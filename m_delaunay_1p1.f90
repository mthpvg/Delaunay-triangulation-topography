subroutine delaunay(points_cpp,triangles_cpp,voisins_cpp,npoints,li,co,gdz)

	use, intrinsic :: iso_c_binding
	use toolbox
	implicit none
	
	double precision,intent(inout)::gdz
	integer,intent(inout)::li,co,npoints
	double precision,intent(inout)::points_cpp(co,li)
	double precision,intent(inout)::triangles_cpp(2*co-6,4)
	double precision,intent(inout)::voisins_cpp(co,co)
	
	real,dimension(:,:),allocatable::points,triangles,rayons,ptslibres,voisins
	real,dimension(:),allocatable::numtridet
	integer::nbelts,ntriangles,nrayons,i,pc,cnumtridet,cptslibres,pp1,pp2,pp3,compteur,cpoints
	real::xc,yc,ax,ay,bx,by,cx,cy,mx,my,r,gdx,gdy
	integer::colmaxvoisins,cvoisins,j,k,l

	nbelts=0

	allocate(points(npoints,4))
	do i=1,npoints
		points(i,:)=points_cpp(i,:)
	end do

	ntriangles=2*npoints-2-4
	nrayons=ntriangles
	allocate(triangles(ntriangles,4)) ; call mafloz(triangles)
	allocate(rayons(nrayons,4)) ; call mafloz(rayons)
	allocate(numtridet(2*ntriangles))
	allocate(ptslibres(2*ntriangles,2))

	gdx=maxval(points(:,1))
	gdy=maxval(points(:,2))
	gdz=maxval(points(:,3))

	!CREATION DES DEUX PREMIERS TRIANGLES AVEC 4 POINTS
	call initialisation(triangles,rayons,points,nbelts) ; cpoints=4

	do while (cpoints/=npoints-1)
		!CHERCHER UN POINT
		call mafloz(ptslibres)
		call vefloz(numtridet)
		do i=1,npoints
			if (points(i,4)==0.) then
				pc=i
				xc=points(i,1) ; yc=points(i,2)
				points(i,4)=1
				cpoints=cpoints+1
				exit
			end if
		end do
		cnumtridet=0
		!A QUELS CERCLES CIRCONSCRITS CE POINT APPARTIENT IL
		do i=1,nbelts
			if ((xc-rayons(i,1))**2+(yc-rayons(i,2))**2<=rayons(i,3)**2) then
				cnumtridet=cnumtridet+1
				numtridet(cnumtridet)=i
			end if
		
		end do

		!LISTING DES POINTS LIBRES
		cptslibres=0
		do i=1,cnumtridet
			ptslibres(cptslibres+1,2)=triangles(int(numtridet(i)),1)
			ptslibres(cptslibres+2,2)=triangles(int(numtridet(i)),2)
			ptslibres(cptslibres+3,2)=triangles(int(numtridet(i)),3)
			cptslibres=cptslibres+3
		end do
		compteur=0
		do i=1,cnumtridet
			call sulifl(triangles,int(numtridet(i))-compteur)
			call sulifl(rayons,int(numtridet(i))-compteur)
			compteur=compteur+1
		end do
		nbelts=nbelts-cnumtridet
		do i=1,nbelts
			triangles(i,4)=i*1.
			rayons(i,4)=i*1.
		end do

		call sudoma(ptslibres,cptslibres)

		call orpoes(xc,yc,ptslibres,points,cptslibres)
		do i=1,cptslibres
			if (i/=cptslibres) then
				pp1=pc ; pp2=int(ptslibres(i,2)) ; pp3=int(ptslibres(i+1,2))
				call ajotri(triangles,rayons,points,pp1,pp2,pp3,nbelts)
			else
				pp1=pc ; pp2=int(ptslibres(i,2)) ; pp3=int(ptslibres(1,2))
				call ajotri(triangles,rayons,points,pp1,pp2,pp3,nbelts)
			end if
		end do
	end do

	do i=1,nbelts
		triangles_cpp(i,:)=triangles(i,:)
	end do

	!RECHERCHE DES VOISINS
	allocate(voisins(npoints,npoints))
	call mafloz(voisins)
	do i=1,npoints
		cvoisins=1 !le premier elements d une ligne de voisins est le nombre de colonnes de cette ligne
		do j=1,ntriangles
			if (triangles(j,1)==i) then
				cvoisins=cvoisins+1
				voisins(i,cvoisins)=triangles(j,2)
				cvoisins=cvoisins+1
				voisins(i,cvoisins)=triangles(j,3)
			elseif (triangles(j,2)==i) then
				cvoisins=cvoisins+1
				voisins(i,cvoisins)=triangles(j,1)
				cvoisins=cvoisins+1
				voisins(i,cvoisins)=triangles(j,3)
			elseif (triangles(j,3)==i) then
				cvoisins=cvoisins+1
				voisins(i,cvoisins)=triangles(j,1)
				cvoisins=cvoisins+1
				voisins(i,cvoisins)=triangles(j,2)
			end if
		end do
		voisins(i,1)=cvoisins-1
		do j=2,cvoisins
			k=j+1
			do while(cvoisins+1>k)
				if (voisins(i,k)==0.) then ; exit ; end if
				if (voisins(i,j)==voisins(i,k)) then
					do l=k,cvoisins
						voisins(i,l)=voisins(i,l+1)
					end do
					voisins(i,1)=voisins(i,1)-1
				else
					k=k+1
				end if
			end do
		end do
	end do


	colmaxvoisins=maxval(voisins(:,1))

	do i=1,npoints
		voisins_cpp(i,1:npoints)=voisins(i,1:npoints)
	end do

	deallocate(points,triangles,rayons,ptslibres)
	deallocate(voisins)
	deallocate(numtridet)

end subroutine delaunay
