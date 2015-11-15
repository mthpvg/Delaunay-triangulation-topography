!TOPOGEN

!Le programme "topogen" assure l elaboration d'un semi de points et la creation
!d un fichier "topogen.txt" contenant les coordonnees des points de ce semi de points.

subroutine topogen(points,l,c,p,npoints)

	use, intrinsic :: iso_c_binding
	use toolbox
	implicit none

	integer,intent(inout)::l,c,npoints
	double precision,intent(inout)::points(c,l)
	double precision,intent(inout)::p
	real,dimension(:,:),allocatable::xyz0p
	real::x,y,rn,zmax
	integer::nx,ny,i,j,d,k

	nx=npoints
	ny=npoints

	allocate(xyz0p((nx-2)*(ny-2),5))

	!Dans cette double boucle sur i,j on remplit la matrice xyz0p avec respectivement
	!dans les deux premieres colonnes les coordonnees x et y dans la troisieme on place
	!l evaluation de la fonction topo en x,y. La quatrieme colonne est remplie de zero
	!par commodite pour le programme "delaunay". Enfin dans la derniere colonne on inscrit
	!des 0 ou des 1 suivant un tirage au sort pondere par le parametre p.
	do i=2,nx-1
	do j=2,ny-1
		xyz0p(j-1+(i-2)*(ny-2),1)=i ; xyz0p(j-1+(i-2)*(ny-2),2)=j
		xyz0p(j-1+(i-2)*(ny-2),3)=topo(real(i),real(j)) ; xyz0p(j-1+(i-2)*(ny-2),4)=0.
		call random_number(rn)
		if (rn<p) then
			xyz0p(j-1+(i-2)*(ny-2),5)=1.
		else
			xyz0p(j-1+(i-2)*(ny-2),5)=0.
		end if
	end do
	end do

	d=sum(xyz0p(:,5))

	npoints=d+4

	points(1,1:4)=(/1.,1.,topo(1.,1.),0./)
	points(2,1:4)=(/1.,ny*1.,topo(1.,ny*1.),0./)
	points(3,1:4)=(/nx*1.,1.,topo(nx*1.,1.),0./)
	points(4,1:4)=(/nx*1.,ny*1.,topo(nx*1.,ny*1.),0./)

	k=0
	do i=1,(nx-2)*(ny-2)
		if (xyz0p(i,5)==1.) then
			k=k+1
			points(4+k,:)=xyz0p(i,1:4)
		end if
	end do

	deallocate(xyz0p)

end subroutine topogen
