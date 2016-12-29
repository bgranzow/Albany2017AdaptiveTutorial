NAME=notch

all: $(NAME)-4p-.smb

$(NAME).geo: $(NAME).cpp
	mpicxx -std=c++11 $(NAME).cpp -o $(NAME) -I${GMODEL_DIR}/include -L${GMODEL_DIR}/lib -lgmodel
	./$(NAME) 0

$(NAME).msh: $(NAME).geo
	gmsh -3 $(NAME).geo -o $(NAME).msh  

$(NAME).smb: $(NAME).msh
	from_gmsh $(NAME).dmg $(NAME).msh $(NAME).smb

$(NAME)-4p-.smb: $(NAME).smb
	mpirun -n 4 split $(NAME).dmg $(NAME).smb $(NAME)-4p-.smb 4

clean:
	rm -rf $(NAME) $(NAME).geo $(NAME).dmg $(NAME).msh $(NAME)*.smb
