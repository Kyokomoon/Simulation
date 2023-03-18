#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "math.h"
#include <unistd.h> 
using namespace std;
#define size_field 1000
#define Lat1_point_map 55.146316 
#define Long1_point_map 82.719252
#define Lat2_point_map 54.848216 
#define Long2_point_map 83.276841
#define PlanetRadius  6372.795  //Km
#define radian  0.0174532   //1градус в радианах
class Coordinates
{
    private:
        int cord_X;
        int cord_Y;
    public:
        Coordinates(int x, int y){
            cord_X = x;
            cord_Y = y;
        }
        Coordinates(){
		cord_X = -1;
		cord_Y = -1;
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
            this->Id = id;
            cord.setCord(x,y);
            this->Distance = 0;
        }
	    Object(){
            this->Id = 0;
            cord.setCord(-1,-1);
            this->Distance = 0;
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
            if(direct == 1 && cord.getCord(1)+mash<=size_field){ //Вверх
                cord.setCord(cord.getCord(0), cord.getCord(1)+mash);
                Distance += mash;
            }
            if(direct == 2 && cord.getCord(0)-mash>=0){//Влево
                cord.setCord(cord.getCord(0)-mash, cord.getCord(1));
                Distance += mash;
            }
            if(direct == 3 && cord.getCord(0)+mash<=size_field){//Вправо
                cord.setCord(cord.getCord(0)+mash, cord.getCord(1));
                Distance += mash;
            }
            if(direct == 4 && cord.getCord(1)-mash>=0){//Вниз
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
        ~Object(){
		delete[] memory;
        }
};
class UserEquipment : public Object { //Наследуемый класс 
    private:
        double Lat; //широта
        double Long; //долгота
    public:
        UserEquipment() : Object(){
            Lat = -1;
            Long = -1;
        }
        UserEquipment(int id, int x, int y) :   
        Object(id, x, y){ //конвертируется автоматически 
            Lat = Lat2_point_map + y * ((Lat1_point_map - Lat2_point_map)/size_field); //конвертация в широту
            Long = Long1_point_map + x * ((Long2_point_map- Long1_point_map)/size_field); //конвертация в долготу
        }
        void convertLatLongCord(int x, int y){ //конвертируем в ручную
            Lat = Lat2_point_map + y * ((Lat1_point_map - Lat2_point_map)/size_field); //конвертация в широту
            Long = Long1_point_map + x * ((Long2_point_map- Long1_point_map)/size_field); //конвертация в долготу
        }
        double getLatLong(int choice_cord){//получаем широту или долготу
            if(choice_cord == 0){
                return Lat;
            }
            else if(choice_cord == 1){
                return Long;
            }
        }
        ~UserEquipment(){
        };
};
void rando(UserEquipment * stek, int count_obj, int count_mov, int mash){ //рандомное перемещение
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
void rand_way(UserEquipment * stek, int count_obj, int count_mov, int mash){
}
void Gaus(UserEquipment * stek, int count_obj, int count_mov, int mash){
}
void Chain(UserEquipment * stek, int count_obj, int count_mov, int mash){
}
int find(int id1, int id2, UserEquipment * stek, int count_obj, int count_mov, int mash){//найти расстояние
	int i, j,rast, a,b,d, x1,y1, x2,y2, way1,way2,choice_mode;
    double lat1=0, lon1 , lat2=0, lon2, delta_lat_in_rad, delta_long_in_rad, sred_lat;
    cout << "\nВыберете вариант вычисления расстояния: В классическом режиме-1, в режиме Lat Long-2: "; //Можно выбрать в каком режиме считать расстояние 
    cin >> choice_mode;
    if(choice_mode == 1){
        for(i=0;i<count_obj;i++){
            
            if(id1 == stek[i].getId()){ //находит координаты указанных объектов
                x1=stek[i].getCord(0);
                y1=stek[i].getCord(1);
                way1 = stek[i].getlengthWay();

            }
            if(id2 == stek[i].getId()){
                x2=stek[i].getCord(0);
                y2=stek[i].getCord(1);
                way2 = stek[i].getlengthWay();
            }
        }
        cout << "\nКоординаты 1 точки в декартовой системе" << x1<<", "<< y1<<")";
	    cout << "\nКоординаты 2 точки в декартовой системе" << x2<<", "<< y2<<")";
        cout << "\nПройденное расстояние 1 точки (" <<way1<<" метров)"<<endl;
	    cout << "\nПройденное расстояние 2 точки (" <<way2<<" метров)"<<endl;
        rast=sqrt(pow((x2-x1),2)+ pow((y2-y1),2));
    }
    else{
        for(i=0;i<count_obj;i++){
            if(id1 == stek[i].getId()){ //находит координаты указанных объектов
                x1=stek[i].getCord(0);
                y1=stek[i].getCord(1);
                stek[i].convertLatLongCord(x1,y1);//конвертация в широту и долготу
                //way1 = stek[i].getlengthWay();
                lat1 =stek[i].getLatLong(0);//получение широты
                lon1 =stek[i].getLatLong(1);//получение долготы
            }
            if(id2 == stek[i].getId()){
                x2=stek[i].getCord(0);
                y2=stek[i].getCord(1);
                stek[i].convertLatLongCord(x2,y2);//конвертация в широту и долготу
                //way2 = stek[i].getlengthWay();
                lat2 =stek[i].getLatLong(0);//получение широты
                lon2 =stek[i].getLatLong(1);//получение долготы
            }
        }
        delta_lat_in_rad = ((radian*lat1) - (radian * lat2)); //Разница широт в радианах
        delta_long_in_rad = ((radian*lon1) - (radian * lon2)); //разница долготы в радианах
        sred_lat = (lat1+lat2)/2; //средняя широта
        cout << "\nКоординаты 1 точки в  системе Lat long: " << lat1<<" Гр Широты, "<< lon1<<" Гр Долготы)";
        cout << "\nКоординаты 2 точки в  системе Lat long: " << lat2<<" Гр Широты, "<< lon2<<" Гр Долготы)";
	    rast = PlanetRadius * sqrt(pow(delta_lat_in_rad,2)+ pow((cos(sred_lat*radian)*delta_long_in_rad),2)); //расстояние между точками
    }
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
    UserEquipment *stek = new UserEquipment[count_obj]; //выделение памяти для массива
    for(i=0;i<count_obj;i++){
        stek[i].memoryInit(count_mov);
    }

    for(i=0;i<count_obj;i++){
        cout << "\nВведите ID объекта № " << i+1 <<" ";  // Пока что id нужно вводить вручную
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
        for(i=(size_field/mash);i>=0;i--){
            for(j=0;j<=(size_field/mash);j++){
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
			cout << "\n\nРасстояние между точками равно: " << rasst<< " Километров" << endl;
		}
		else if(choice == 2)cout << "\nПрограмма завершена";
		else cout << "\nError:Неверная команда\n";
	}
    //очищение памяти
	delete[] stek;
}
