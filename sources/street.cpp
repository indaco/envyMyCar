/****************************************************************************
* NVMC                                                                      *
* EnVy My Car																																*
*                                                                           *
* Fabio Ganovelli                                                           *
*                                                                           *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *   
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/
/****************************************************************************
  History

$Log: street.cpp,v $
Revision 1.3  2007/07/04 13:28:30  ganovelli
halfway  version for thumbnails

*****************************************************************************/

#include <street.h>

void Street::Save(FILE * f){
	
	fprintf(f,"PATH %d\n",this->path.size());
	for(unsigned int i= 0; i < this->path.size();++i)
		fprintf(f,"%f %f %f %f %f %f\n",
		this->path[i][0].P()[0],this->path[i][0].P()[1],this->path[i][0].P()[2],
		this->path[i][1].P()[0],this->path[i][1].P()[1],this->path[i][1].P()[2]);

	fprintf(f,"TUNNELS %d\n",this->tunnels.size());
	for(unsigned int j= 0; j < this->tunnels.size();++j){
		const Tunnel & t = this->tunnels[j];
		fprintf(f,"TUNNNELHEIGHT %f\n",t.heigth);
		fprintf(f,"TUNNNELLENGTH %d\n",t.path.size());
		for(unsigned int i= 0; i < t.path.size();++i)
			fprintf(f,"%f %f %f %f %f %f\n",
			t.path[i][0].P()[0],t.path[i][0].P()[1],t.path[i][0].P()[2],
			t.path[i][1].P()[0],t.path[i][1].P()[1],t.path[i][1].P()[2]);
	}

	fprintf(f,"ENTRYPOINTS %d\n",this->entry_points.size());
	for(unsigned int i= 0; i < this->entry_points.size();++i)
		fprintf(f,"%f %f %f \n",
		this->entry_points[i][0],this->entry_points[i][1],this->entry_points[i][2]);

}
void Street::Load(FILE * f){
	char _[255];
	int sz,sz1;
	fscanf(f,"%s %d\n",_,&sz);
	this->path.resize(sz);
	for(int i= 0; i < sz;++i)
		fscanf(f,"%f %f %f %f %f %f ",
		&this->path[i][0].P()[0],&this->path[i][0].P()[1],&this->path[i][0].P()[2],
		&this->path[i][1].P()[0],&this->path[i][1].P()[1],&this->path[i][1].P()[2]);

	fscanf(f,"%s %d\n",_,&sz);
	this->tunnels.resize(sz);
	for(int j= 0; j < sz;++j){
		 Tunnel & t = this->tunnels[j];
		fscanf(f,"%s %f\n",_,&t.heigth);
		fscanf(f,"%s %d\n",_,&sz1);
		t.path.resize(sz1);
		for(int i= 0; i <sz1;++i){
		fscanf(f,"%f %f %f %f %f %f\n",
		&t.path[i][0].P()[0],&t.path[i][0].P()[1],&t.path[i][0].P()[2],
		&t.path[i][1].P()[0],&t.path[i][1].P()[1],&t.path[i][1].P()[2]);
		}
	}

	fscanf(f,"%s %d\n",_,&sz);
	this->entry_points.resize(sz);
	for(int i= 0; i < sz;++i)
		fscanf(f,"%f %f %f ",
		&this->entry_points[0][0],&this->entry_points[0][1],&this->entry_points[0][2]);

}
