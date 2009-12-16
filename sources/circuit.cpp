#include <circuit.h>
#include <stdlib.h>

void Circuit::Save(char * filename){

	FILE * f = fopen(filename,"w");

	/** Save the bounding box */
	fprintf(f,"BBOX %f %f %f %f %f %f \n",
		this->bbox.min[0],this->bbox.min[1],this->bbox.min[2],
		this->bbox.max[0],this->bbox.max[1],this->bbox.max[2]);

	/** Save the buildings */
	fprintf(f,"BUILDINGS %d\n",buildings.size());
	for(unsigned int i = 0; i <buildings.size(); ++i){
		fprintf(f,"BUILDING %d %d\n",i,buildings[i].footprint.size());
		for(unsigned int j = 0; j <buildings[i].footprint.size(); ++j)
			fprintf(f,"%f %f %f\n",
				buildings[i].footprint[j].P()[0],
				buildings[i].footprint[j].P()[1],
				buildings[i].footprint[j].P()[2]);
		fprintf(f,"height %f\n",buildings[i].height);
	}

	/** Save the tree*/
	fprintf(f,"TREES %d\n",trees.size());
	for(unsigned int i = 0; i <trees.size(); ++i)
		fprintf(f,"%f %f %f %f\n",trees[i].pos[0],trees[i].pos[1],trees[i].pos[2],trees[i].height);

	

	/** Save the street*/
	this->street.Save(f);

}

void Circuit::Load(char * filename){
	char _[255];
	int sz,sz1,h;
	FILE * f = fopen(filename,"r");
	fscanf(f,"%s %f %f %f %f %f %f \n",_,
		&this->bbox.min[0],&this->bbox.min[1],&this->bbox.min[2],
		&this->bbox.max[0],&this->bbox.max[1],&this->bbox.max[2]);

	fscanf(f,"%s %d",_,&sz);
	buildings.resize(sz);
	for(int i = 0; i <sz; ++i){
		fscanf(f,"%s %d %d",_,&h,&sz1);
		buildings[i].footprint.resize(sz1);
		for(int j = 0; j <sz1; ++j)
			fscanf(f,"%f %f %f",
				&buildings[i].footprint[j].P()[0],
				&buildings[i].footprint[j].P()[1],
				&buildings[i].footprint[j].P()[2]);
		fscanf(f,"%s %f",_,&buildings[i].height);
	}

	fscanf(f,"%s %d\n",_,&sz);
	trees.resize(sz);
	for(int i = 0; i <sz; ++i)
		fscanf(f,"%f %f %f %f",&trees[i].pos[0],&trees[i].pos[1],&trees[i].pos[2],&trees[i].height);

	this->street.Load(f);

}

