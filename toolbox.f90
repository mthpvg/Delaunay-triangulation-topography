module toolbox
implicit none
contains

!DELAUNAY
!LEcture et ALlocation d une MAtrice
subroutine lealma(m,nom)
	real,dimension(:,:),allocatable,intent(inout)::m
	character(LEN=*),intent(in)::nom
	integer::li,co,i
	open(UNIT=10,FILE=nom)
	read(10,*)li,co ; allocate(m(li,co))
	do i=1,li ; read(10,*)m(i,:) ; end do
	close(10)
end subroutine lealma

!AFfiche VEcteur FLottant
subroutine afvefl(tab)
	REAL,dimension(:),intent(in)::tab
	write(*,*)tab(:)
end subroutine afvefl

!AFfiche MAtrice FLottant
subroutine afmafl(tab)
	REAL,dimension(:,:),intent(in)::tab
	integer::l,i
	l=size(tab,1)
	do i=1,l ; write(*,*)tab(i,:) ; end do
end subroutine afmafl

!SUpprimer LIgne FLottant
subroutine sulifl(m,n)
	real,dimension(:,:),intent(inout)::m
	integer,intent(in)::n
	integer::l,i
	l=size(m,1)
	do i=1,l-1
		if (i>=n) then
			m(i,:)=m(i+1,:)
		end if
	end do
	m(l,:)=0.
end subroutine sulifl

!CEntre RAyon CIrconscrit
subroutine ceraci(ax,ay,bx,by,cx,cy,mx,my,r)
	real,intent(in)::ax,ay,bx,by,cx,cy
	real,intent(out)::mx,my,r
	real::dx,dy,ex,ey,aem,adm,bem,bdm
	real,dimension(2)::ab,ac,bc,oab,obc
	ab(1)=bx-ax ; ab(2)=by-ay
	ac(1)=cx-ax ; ac(2)=cy-ay
	bc(1)=cx-bx ; bc(2)=cy-by
	!Trois tests pour savoir si le triangle est rectangle, dans ce cas le centre est le milieu de l'hypothénuse.
	if (dot_product(ab,ac)==0.) then ; mx=(bx+cx)/2. ; my=(by+cy)/2.
		elseif (dot_product(ac,bc)==0.) then ; mx=(ax+bx)/2. ; my=(ay+by)/2.
		elseif (dot_product(ab,bc)==0.) then ; mx=(ax+cx)/2. ; my=(ay+cy)/2.
		else
		!sinon on calcule l'intersection des médiatrices
			dx=(ax+bx)/2. ; dy=(ay+by)/2.
			ex=(bx+cx)/2. ; ey=(by+cy)/2.
			oab(1)=-ab(2) ; oab(2)=ab(1)
			obc(1)=-bc(2) ; obc(2)=bc(1)
			!deux cas particuliers d'intersection de droite : si horizontalité ou verticalité
			if (oab(1)==0.) then
				aem=obc(2)/obc(1) ; bem=ey-aem*ex ; mx=dx ; my=aem*mx+bem
			elseif (obc(1)==0.) then
				adm=oab(2)/oab(1) ; bdm=dy-adm*dx ; mx=ex ; my=adm*mx+bdm
			else
			!cas général
				aem=obc(2)/obc(1) ; adm=oab(2)/oab(1)
				bem=ey-aem*ex ; bdm=dy-adm*dx ; mx=(bdm-bem)/(aem-adm) ; my=aem*mx+bem
			endif
	endif
	r=sqrt((mx-ax)**2+(my-ay)**2)
end subroutine ceraci

!Triage Croissant VEcteur REal
subroutine tcvere(vect,cpd)
	real,dimension(:,:),intent(inout)::vect
	integer,intent(in)::cpd
	real::var,var2
	integer::posi,i
	do i=1,cpd
		posi=maxloc(vect(1:cpd+1-i,1),1)
		var=vect(cpd+1-i,1) ; var2=vect(cpd+1-i,2)
		vect(cpd+1-i,1)=vect(posi,1)
		vect(cpd+1-i,2)=vect(posi,2)
		vect(posi,1)=var ; vect(posi,2)=var2
	end do
end subroutine tcvere

!MAtrice FLOttant a Zero
subroutine mafloz(tab)
	REAL,dimension(:,:),intent(inout)::tab
	integer::l,i
	l=size(tab,1)
	do i=1,l ; tab(i,:)=0. ; end do
end subroutine mafloz

!VEcteur FLOttant a Zero
subroutine vefloz(tab)
	REAL,dimension(:),intent(inout)::tab
	tab(:)=0.
end subroutine vefloz

!AJOut TRIangle
subroutine ajotri(triangles,rayons,points,pp1,pp2,pp3,nbelts)
	real,dimension(:,:),intent(inout)::triangles,rayons,points
	integer,intent(in)::pp1,pp2,pp3
	integer,intent(inout)::nbelts
	real::ax,ay,az,bx,by,cx,cy,mx,my,r
	ax=points(pp1,1) ; ay=points(pp1,2)
	bx=points(pp2,1) ; by=points(pp2,2)
	cx=points(pp3,1) ; cy=points(pp3,2)
	points(pp1,4)=1. ; points(pp2,4)=1. ; points(pp3,4)=1.
	nbelts=nbelts+1
	call ceraci(ax,ay,bx,by,cx,cy,mx,my,r)
	rayons(nbelts,1)=mx ; rayons(nbelts,2)=my
	rayons(nbelts,3)=r ; rayons(nbelts,4)=nbelts*1.
	triangles(nbelts,1)=pp1*1. ; triangles(nbelts,2)=pp2*1.
	triangles(nbelts,3)=pp3*1. ; triangles(nbelts,4)=nbelts*1.
	
end subroutine ajotri

!Initialisation
!Creation des deux premiers triangles a partir des 4 points formant
!les extremites du domaine
subroutine initialisation(triangles,rayons,points,nbelts)
	real,dimension(:,:),intent(inout)::rayons,triangles
	real,dimension(:,:),intent(inout)::points
	integer,intent(inout)::nbelts
	integer::pp1,pp2,pp3
	pp1=1 ; pp2=2 ; pp3=3
	call ajotri(triangles,rayons,points,pp1,pp2,pp3,nbelts)
	pp1=2 ; pp2=3 ; pp3=4
	call ajotri(triangles,rayons,points,pp1,pp2,pp3,nbelts)
end subroutine initialisation

!ORganisation de POints dans l ESpace
subroutine orpoes(x,y,ptslibres,points,cpd)
	real,dimension(:,:),intent(inout)::ptslibres
	real,dimension(:,:),intent(in)::points
	real,intent(in)::x,y
	integer,intent(in)::cpd
	integer::i
	real::xe,ye,alpha
	!L'objectif de cette subroutine est d'organiser les points (ptslibres) par ordre selon le sens trigonométrique. On cherche donc
	!pour chacun l'angle qui le caractérise.
	do i=1,cpd
		alpha=0.
		xe=points(int(ptslibres(i,2)),1)-x
		ye=points(int(ptslibres(i,2)),2)-y
		!Pour trouver cet angle on utilise l'atan en prenant en compte la discontinuité de la fonction ainsi que ses valeurs remarquables
		!à l'aide des tests suivants 
		if (xe==0. .and. ye>0.) then
			ptslibres(i,1)=3.14/2.
		elseif (xe==0. .and. ye<0.) then
			ptslibres(i,1)=3*3.14/2.
		else
			if (xe>0. .and. ye>=0.) then
				ptslibres(i,1)=atan(abs(ye)/abs(xe))
			elseif (xe<0. .and. ye>=0.) then
				ptslibres(i,1)=3.14-atan(abs(ye)/abs(xe))
			elseif (xe<0. .and. ye<=0.) then
				ptslibres(i,1)=atan(abs(ye)/abs(xe))+3.14
			elseif (xe>0. .and. ye<=0.) then
				ptslibres(i,1)=2*3.14-atan(abs(ye)/abs(xe))
			end if
		end if
	end do
	call tcvere(ptslibres,cpd)
endsubroutine orpoes

!SUpprimer DOublon MAtrice
subroutine sudoma(ptslibres,cptslibres)
	real,dimension(:,:),intent(inout)::ptslibres
	integer,intent(inout)::cptslibres
	integer::i,j,c,k
	c=0
	do i=1,cptslibres
		j=i+1
		do while(cptslibres+1>j)
			if (ptslibres(j,2)==0.) then ; exit ; end if
				if (ptslibres(i,2)==ptslibres(j,2)) then
					do k=j,cptslibres
						ptslibres(k,2)=ptslibres(k+1,2)
					end do
					c=c+1
				else
					j=j+1
				end if
		end do
	end do
	cptslibres=cptslibres-c
end subroutine sudoma

!END DELAUNAY


!La fonction topo evalue une somme de gaussienne en un point de l espace de
!coordonnees x,y.
real function topo(x,y)
	real,intent(in)::x,y
	topo=16-(x-70)**2*(y-70)**2/6000000+x*y/7500+x/35-y**(1/2)+&
	&1*exp(-0.1*(x-35)**2)*exp(-0.1*(y-45)**2)*5-1*exp(-0.05*(x-45)**2)*&
	&exp(-0.005*(y-35)**2)*5+1*exp(-0.0005*(x-70)**2)*exp(-0.075*(y-70)**2)*3+&
	&1*exp(-0.005*(x-95)**2)*exp(-0.005*(y-95)**2)*7-&
	&1*exp(-0.00025*(x-70)**2)*exp(-0.005*(y-70)**2)*4+&
	&1*exp(-0.0005*(x-50)**2)*exp(-0.075*(y-70)**2)*4+&
	&1*exp(-0.1*(x-30)**2)*exp(-0.1*(y-40)**2)*4+&
	&1*exp(-0.0025*(x-80)**2)*exp(-0.025*(y-85)**2)*6-&
	&1*exp(-0.01*(x-50)**2)*exp(-0.025*(y-100)**2)*7-&
	&1*exp(-0.050*(x-70)**2)*exp(-0.00075*(y-100)**2)*8+&
	&1*exp(-0.020*(x-95)**2)*exp(-0.030*(y-40)**2)*9+&
	&1*exp(-0.040*(x-90)**2)*exp(-0.020*(y-50)**2)*7+&
	&1*exp(-0.020*(x-80)**2)*exp(-0.010*(y-60)**2)*6-&
	&1*exp(-0.005*(x-70)**2)*exp(-0.001*(y-60)**2)*5-&
	&1*exp(-0.0005*(x-45)**2)*exp(-0.01*(y-45)**2)*8+&
	&1*exp(-0.01*(x-70)**2)*exp(-0.01*(y-110)**2)*5+&
	&1*exp(-0.01*(x-110)**2)*exp(-0.01*(y-30)**2)*8+&
	&1*exp(-0.1*(x-110)**2)*exp(-0.1*(y-30)**2)*2+&
	&1*exp(-0.1*(x-100)**2)*exp(-0.1*(y-25)**2)*3+&
	&1*exp(-0.1*(x-85)**2)*exp(-0.1*(y-35)**2)*5-&
	&1*exp(-0.01*(x-30)**2)*exp(-0.1*(y-110)**2)*5-&
	&1*exp(-0.001*(x-50)**2)*exp(-0.01*(y-95)**2)*2+&
	&1*exp(-0.0075*(x-35)**2)*exp(-0.01*(y-80)**2)*9-&
	&1*exp(-0.20*(x-34)**2)*exp(-0.2*(y-79)**2)*4
end function topo

end module toolbox
