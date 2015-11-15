!Lighter à partir d'un Semi de Points et de la liste des voisins de ces derniers allège le SDP de la façon suivante.
!Tout d'abord il somme la différence d'altitude entre le point et ses voisins si celle-ci dépasse une certaine valeur
!et qu'il n'y a pas eu trop de suppression de points parmi son voisinage alors il est supprimé.

subroutine lighter(points_cpp,voisins_cpp,polic,l,c,npoints,nlighter)

	use, intrinsic :: iso_c_binding
	use toolbox
	implicit none

	integer,intent(inout)::l,c,npoints,nlighter
	double precision,intent(inout)::points_cpp(c,l)
	double precision,intent(inout)::voisins_cpp(c,c)
	double precision,intent(inout)::polic(c,l)
	real,dimension(:,:),allocatable::points,voisins
	real,dimension(:,:),allocatable::points_light

	integer::nvoisins,i,j,nbvoisins,k
	real::somme,gdx,gdy,gdz,somme2

	allocate(points(c,4))
	allocate(voisins(c,c))
	allocate(points_light(c,4))
	call mafloz(points)
	call mafloz(voisins)
	call mafloz(points_light)


	do i=1,npoints
		points(i,:)=points_cpp(i,:)
		voisins(i,1:npoints)=voisins_cpp(i,1:npoints)
	end do

	points(:,4)=0.

	gdx=maxval(points(:,1))
	gdy=maxval(points(:,2))
	gdz=maxval(points(:,3))

	nvoisins=npoints

	
	do i=5,npoints
		somme=0.
		somme2=0.
		!On somme la différence d'altitude entre le points et ses voisins
		!et on compte le nombre de voisins déjà supprimé.
		do j=2,int(voisins(i,1))+1
			somme=somme+abs(points(int(voisins(i,j)),3)-points(i,3))/points(i,3)
			somme2=somme2+points(int(voisins(i,j)),4)
		end do
		somme=somme/voisins(i,1)
		!Si la moitié des voisins a déjà été supprimé
		if (somme2<=int(voisins(i,1))*0.5) then
			!Si la somme des différences d'altitudes est inférieur à une constante
			if (somme<0.02) then
				!Ce point ne sera pas gardé
				points(i,4)=1.
			end if
		end if
	end do

	nlighter=sum(points(:,4))

	nlighter=npoints-nlighter

	k=0
	do i=1,npoints
		if (points(i,4)==0.) then
			k=k+1
			points_light(k,:)=points(i,:)
			polic(k,:)=points(i,:)
		end if
	end do

	deallocate(points,voisins,points_light)

end subroutine lighter
