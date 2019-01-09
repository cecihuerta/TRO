#include <vector>

using namespace std;

//OPERADOR INTERSECCIÓN: verifica que para 2 trayectorias (principal y alternativa), se intersectan en al menos un punto.
//El operador intersección (entre segmentos) utiliza un valor de tolerancia propio del operador AlmostEqual.

bool Intersects(Line& PLine, Line& ALine){

	assert(PLine.IsDefined()); 
  	assert(ALine.IsDefined());
  	if(PLine.IsEmpty() || ALine.IsEmpty())
  		return false;

  	assert(PLine.IsOrdered());
    assert(ALine.IsOrdered());

	HalfSegment hs1, hs2;

	for(int i = 0; i < Size(); i++){
		PLine.Get( i, hs1 );
		if(hs1.IsLeftDomPoint()){
			for(int j = 0; j < l.Size(); j++){
				ALine.Get(j, hs2);
				if(hs2.IsLeftDomPoint()){
					if(hs1.Intersects(hs2)){ //intersección entre segmentos
						return true;
					}
				}
			}
		}
	}
	return false;
}


//OPERADOR SUBSECUENCIA: verifica que para 2 trayectorias (principal y alternativa), se cumple que cada punto de la trayectoria alternativa
//se mapea o está cerca de un punto de la trayectoria principal. 
//Todos los puntos de la trayectoria alternativa deben ser considerados.
//El cálculo de distancia se hace de punto (T. alternativa) a segmento (T. principal).

bool Subsequence(Line& PLine, Line& ALine){

	assert(PLine.IsDefined()); 
  	assert(ALine.IsDefined());
  	if(PLine.IsEmpty() || ALine.IsEmpty())
  		return false;

  	assert(PLine.IsOrdered());
    assert(ALine.IsOrdered());

	Point p;
	HalfSegment hs;
	double delta = 0.000001;
	double minDist = numeric_limits<double>::max();
	double dist = -1.0;
	int cont = 0;

	for(int i = 0; i < ALine.Vertices(); i++){ 
		ALine.Get(i, p);
		for(int j = 0; j < PLine.Size(); j++){
			PLine.Get(j, hs);
			if(hs.IsLeftDomPoint()){
				dist = hs.Distance(p); //distancia de punto a segmento
				//if(dist >= 0.0){ //evaluar condición
					minDist = MIN(minDist, dist);
				//}//else{}
			}else{
				return false;
			}
		}
		if(minDist <= delta){
			cont++;
		}else{
			return false;
		}
	}
	if(ALine.Vertices() == cont){
		return true;
	}	
}

//OPERADOR AGRUPACIÓN: verifica que para 2 trayectorias (principal y altenativa), se cumple que cada punto de la trayectoria alternativa
//agrupa o está cerca de un subconjunto S de puntos contiguos de la trayectoria principal.
//Todos los puntos de ambas trayectorias deben ser considerados.
//El cálculo de distancia se hace de punto (T. altenativa) a punto (T. principal).

bool Similarity(Line& PLine, Line& ALine){

	assert(PLine.IsDefined()); 
  	assert(ALine.IsDefined());
  	if(PLine.IsEmpty() || ALine.IsEmpty())
  		return false;

  	assert(PLine.IsOrdered());
    assert(ALine.IsOrdered());
	
	Point p1, p2;
	double delta = 0.000001;
	double minDist;
	vector<Point> S;
	int aux = 0;

	for(int i = 0; i < ALine.Vertices(); i++){
		ALine.Get(i, p1);
		for(int j = aux; j < PLine.Vertices(); j++){
			PLine.Get(j, p2);
			minDist = p1.Distance(p2); //distancia de punto a punto
			if(minDist >= 0.0){
				if(minDist <= delta){
					S.push_back(p2);
				}else{
					if(j = 0){
						return false;
					}else{
						aux = j; //aux toma el valor de j
						break;
					}
				}
			}
		}
	}
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                 