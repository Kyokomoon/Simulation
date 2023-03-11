#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "math.h"
#include <unistd.h> 
using namespace std;
#define size_field 1000
class Coordinates
{
    private:
        int cord_X;
        int cord_Y;
        double Lat;
        double Long;
    public:
        Coordinates(int x, int y){
            cord_X = x;
            cord_Y = y;
            Lat = -1;
            Long = -1;
        }
        Coordinates(){
		cord_X = -1;
		cord_Y = -1;
        Lat = -1;
        Long = -1;
        }
        void setCord(int x, int y){
            cord_X = x;
            cord_Y = y;
        }
        int getCord(int choice_cord){
            if(choice_cord == 0){
                return cord_X;
            }
            else if(choice_cord == 1){
                return cord_Y;
            }
		    else return -1;
        }
        double getLangLongCord(int choice_cord){
            if(choice_cord == 0){
                return Long;
            }
            else if(choice_cord == 1){
                return Lat;
            }
		    else return -1;
        }
        void convertInLatLong(int cord_x , int cord_y){ //при условии, если поле занимает 1/4 сферы
            Lat = cord_y * ((float)90/size_field); //Широта
            Long = cord_x * ((float)180/size_field); //Долгота
        }
        ~Coordinates(){
        }
};
class Object
{
    private:
        int Id;
        int Distance;
        Coordinates cord;
        Coordinates *memory;
    public:
        Object(int id, int x, int y){
            Id = id;
            cord.setCord(x,y);
            Distance = 0;
        }
	    Object(){
            Id = 0;
            cord.setCord(-1,-1);
            Distance = 0;
	    }
        void memoryInit(int count_mov){
            memory = new Coordinates[count_mov];
        }
        int memoryGet(int n, int choice_cord){
            if(choice_cord == 0){
                return memory[n].getCord(0);
            }
            else if(choice_cord == 1){
                return memory[n].getCord(1);
            }
            else return -1;
        }
        int getId(){
            return Id;
        }
        void setId(int id){
            Id = id;
        }
        void setCord(int x, int y, int i){
            cord.setCord(x,y);
            memory[i].setCord(x,y);
        }
        int getCord(int choice_cord){
            if(choice_cord == 0){
                return cord.getCord(0);
            }
            else if(choice_cord == 1){
                return cord.getCord(1);
            }
		else return -1;
        }
        void move(int direct, int mash, int mov){
            if(direct == 1 && cord.getCord(1)+mash<size_field){ //Вверх
                cord.setCord(cord.getCord(0), cord.getCord(1)+mash);
                Distance += mash;
            }
            if(direct == 2 && cord.getCord(0)-mash>0){//Влево
                cord.setCord(cord.getCord(0)-mash, cord.getCord(1));
                Distance += mash;
            }
            if(direct == 3 && cord.getCord(0)+mash<size_field){//Вправо
                cord.setCord(cord.getCord(0)+mash, cord.getCord(1));
                Distance += mash;
            }
            if(direct == 4 && cord.getCord(1)-mash>0){//Вниз
                cord.setCord(cord.getCord(0), cord.getCord(1)-mash);
                Distance += mash;
            }
            else{ //На месте
                cord.setCord(cord.getCord(0), cord.getCord(1));
            }
            memory[mov] = cord;
        }
        int getlengthWay(){
            return Distance;
        }
        void convertLatLongCord(){
            cord.convertInLatLong(cord.getCord(0), cord.getCord(1));
        }
        double getLatLongCord(int choice_cord){
            return cord.getLangLongCord(choice_cord);
        }
        ~Object(){
		delete[] memory;
        }
};

void rando(Object * stek, int count_obj, int count_mov, int mash){ //рандомное перемещение
    int direct, i, obj;
    for(obj=0;obj<count_obj;obj++){
        for(i=1;i<count_mov;i++){
            direct = rand()%5;
            if(direct >= 0 || direct <= 4){ //На месте
                stek[obj].move(direct, mash, i);
            }
		    else stek[obj].move(0, mash, i);
        }
    }
}
//заглушки
void rand_way(Object * stek, int count_obj, int count_mov, int mash){
}
void Gaus(Object * stek, int count_obj, int count_mov, int mash){
}
void Chain(Object * stek, int count_obj, int count_mov, int mash){
}
int find(int id1, int id2, Object * stek, int count_obj, int count_mov, int mash){//найти расстояние
	int i, j,rast, a,b,d, x1,y1, x2,y2, way1,way2;
    double lat1, lon1 , lat2, lon2;
	for(i=0;i<count_obj;i++){
		if(id1 == stek[i].getId()){ //находит координаты указанных объектов
			x1=stek[i].getCord(0);
			y1=stek[i].getCord(1);
			way1 = stek[i].getlengthWay();
            stek[i].convertLatLongCord();
            lat1 = stek[i].getLatLongCord(1);
            lon1 = stek[i].getLatLongCord(0);

		}
		if(id2 == stek[i].getId()){
			x2=stek[i].getCord(0);
			y2=stek[i].getCord(1);
			way2 = stek[i].getlengthWay();
            stek[i].convertLatLongCord();
            lat2 = stek[i].getLatLongCord(1);
            lon2 = stek[i].getLatLongCord(0);
		}
	}
	cout << "\nКоординаты 1 точки в декартовой системе" << x1<<", "<< y1<<")";
	cout << "\nКоординаты 2 точки в декартовой системе" << x2<<", "<< y2<<")";
    cout << "\nКоординаты 1 точки в  системе Lat long: " << lat1<<" Гр Широты, "<< lon1<<" Гр Долготы)";
    cout << "\nКоординаты 2 точки в  системе Lat long: " << lat2<<" Гр Широты, "<< lon2<<" Гр Долготы)";
	cout << "\nПройденное расстояние 1 точки (" <<way1<<" метров)"<<endl;
	cout << "\nПройденное расстояние 2 точки (" <<way2<<" метров)"<<endl;
	rast=sqrt(pow((x2-x1),2)+ pow((y2-y1),2));
	return rast;
}
int main(){
    srand(time(NULL));
    int i,j,objt,x,y, chek=0, count_obj, count_mov, id, mash, choice, mov;
    cout << "\nВведите масштаб(рекоммендуется 1 к 20) 1к : ";
    cin >> mash;
    cout << "\nВведите количество объектов: ";
    cin >> count_obj;
    cout << "\nВведите количество движений: ";
    cin >> count_mov;
    Object *stek = new Object[count_obj]; //выделение памяти для массива
    for(i=0;i<count_obj;i++){
        stek[i].memoryInit(count_mov);
    }

    for(i=0;i<count_obj;i++){
        cout << "\nВведите ID объекта № " << i+1 <<" ";  // Пока что id нужно вводить вручную, проверка на одинаковые значения пока не предусмотренна 
        cin >> id;
        chek = 0;
        for(j=0;j<count_obj;j++){
            if(id == stek[j].getId())chek=1;
        }
        if(chek==0)stek[i].setId(id);
        else{
            cout << "\nID должен отличаться"<<endl;
            i--;
        }
    }
    //пояснение за масштаб, он нужен что бы было удобно отображать на экране поле, все координаты остаются в масштабе 1к1, для правильного вычисления расстояния  
    for(i=0;i<count_obj;i++){
        x = (rand()%(size_field/mash))*mash;//масштаб. В данном случае x и y это машсштабируемые координаты для отображения на экране(в структуре они все еще 1к1)
        y = (rand()%(size_field/mash))*mash;//масштаб
        for(j=0;j<count_obj;j++){//выдача объектам начальных координат, одинаковые координаты не проходят
            if(x!=stek[j].getCord(0) && y!=stek[j].getCord(1)){
                chek=1;
            }
            else{
                chek=0;
                continue;
            }
        }
        if(chek==1){
            stek[i].setCord(x,y,0); //Начальные координаты
        }
        else i--;
    }
    cout << "\nВыберете вариант движения: 1-random, 2-Random Waypoint, 3-Gaussian-Markov, 4-Markov Chains >> " <<endl; //заготовка 
    cin >> choice;
    if(choice == 1) rando(stek,count_obj, count_mov, mash);
    else if(choice == 2) rand_way(stek,count_obj, count_mov, mash);//заготовка
    else if(choice == 3) Gaus(stek,count_obj, count_mov, mash);//заготовка
    else if(choice == 4) Chain(stek,count_obj, count_mov, mash);//заготовка
    //отрисовка поля и объектов с учетом масштаба
	for(mov=0;mov<count_mov;mov++){
		sleep(1); // задержка 1 секунда
        system("clear");
        for(i=(size_field/mash);i>0;i--){
            for(j=0;j<(size_field/mash);j++){
		        chek=0;
                for(objt=0;objt<count_obj;objt++){
                    if(i==((stek[objt].memoryGet(mov,1))/mash) && j == ((stek[objt].memoryGet(mov,0))/mash)){ //если встречается координата объекта
                        cout << "0 ";
                        chek=1;
                    }
                    else if ((i!=((stek[objt].memoryGet(mov,1))/mash) || j != ((stek[objt].memoryGet(mov,0))/mash)) && (chek == 0)) chek = 0;
                }
                if(chek==0) cout << "* "; //если объект не встретился
	    }
        cout <<"\n";
    	}
    }
	choice = 0;
    int id_1,id_2, rasst;
	while(choice!=2){
		cout<< "\n\nХотите узнать расстояние между точками? 1-Da 2-Net : ";
		cin >> choice;
		if(choice == 1){
			cout << ("\nВведите ID 1точки: ");
			cin >> id_1;
			cout << ("\nВведите ID 2точки: ");
			cin >> id_2;
			rasst=find(id_1,id_2,stek,count_obj, count_mov,mash);
			cout << "\n\nРасстояние между точками равно: " << rasst<< " метров" << endl;
		}
		else if(choice == 2)cout << "\nПрограмма завершена";
		else cout << "\nError:Неверная команда\n";
	}
    //очищение памяти
	delete[] stek;
}