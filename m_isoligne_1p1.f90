!Le principe ici est de former deux groupes de points. L'un supérieur à une altitude donnée, l'autre inférieur.
!Ensuite connaisant les voisins de chaque point on boucle sur les dits points, en vérifiant que : est ce que ce point est inférieur
!à l'altitude et parmi ses voisins y a t'il des points qui ne le sont pas. Si l'un au moins des voisins ne l'est pas. Le point est
!membre de l'isoligne recherché.

	subroutine isoligne(points_cpp,voisins_cpp,isolignes_cpp,p,l,c,npoints,cisolignes)

	use, intrinsic :: iso_c_binding
	use toolbox
	implicit none

	integer,intent(inout)::l,c,npoints,cisolignes
	double precision,intent(inout)::p
	double precision,intent(inout)::voisins_cpp(c,c)
	double precision,intent(in)::points_cpp(c,l)
	double precision,intent(inout)::isolignes_cpp(c)

	real,dimension(:,:),allocatable::voisins,points
	real,dimension(:,:),allocatable::entourage
	real,dimension(:),allocatable::isolignes
	integer::nvoisins,i,j,pactuel,nbvoisins,phmax,cinf
	integer::pisoligne,compteur
	real::gdx,gdy,gdz,iso,etat1,etat2
	
	allocate(points(npoints,4))

	do i=1,npoints
		points(i,:)=points_cpp(i,:)
	end do

	gdx=maxval(points(1:npoints,1))
	gdy=maxval(points(1:npoints,2))
	gdz=maxval(points(1:npoints,3))

	nvoisins=npoints
	allocate(isolignes(npoints))
	allocate(entourage(2,npoints))
	call vefloz(isolignes)
	call mafloz(entourage)
	allocate(voisins(npoints,npoints))

	do i=1,npoints
		voisins(i,:)=voisins_cpp(i,:)
	end do

	!on définit l'altitude de l'isoligne voulue.
	iso=gdz*p
	!cinf est le compteur de point contenu dans l'isoligne
	cinf=0

	!Dans cette boucle on différencie les points supérieurs des points inférieurs à l'altitude voulue
	do i=5,npoints
			if (points(i,3)>iso) then
				points(i,4)=1.
			else
				points(i,4)=2.
				cinf=cinf+1
			end if
	end do

	do i=1,5
		points(i,4)=2.
	end do

	cisolignes=0
	!A présent on regarde si l'un des points inférieurs est voisin d'un point supérieur
	do i=5,npoints
		if (points(i,4)==2.) then
			compteur=0
			do j=2,int(voisins(i,1))+1
				if (points(int(voisins(i,j)),4)==2.) then
					compteur=compteur+1
				end if
			end do
			if (compteur/=int(voisins(i,1))) then
				cisolignes=cisolignes+1
				isolignes(cisolignes)=i
			end if
		end if
	end do

	do i=1,cisolignes
		isolignes_cpp(i)=isolignes(i)	
	end do

	deallocate(points,voisins)
	deallocate(isolignes,entourage)

end subroutine isoligne
