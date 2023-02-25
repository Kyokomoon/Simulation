#include<stdio.h> //работоспособность проверенна на Linux, пожалуйста запускайте программу в среде Linux, через терминал(тк для отображения используеться консольная команда)
#include<time.h>
#include<unistd.h>//для использования sleep
#include<stdlib.h>
#include"math.h"
typedef struct object{
    int id;
    int cord[2]; //2 координаты X и Y
    int **memory;// двумерный массив,хранящий историю перемещений
}obj;
void rando(obj * stek, int count_obj, int count_mov, int mash){ //рандомное перемещение
    int direct, i, j;
    for(j=0;j<count_obj;j++){
        for(i=1;i<count_mov;i++){
            direct = rand()%5;
            if(direct == 0){ //На месте
                stek[j].cord[0] = stek[j].cord[0];
                stek[j].cord[1] = stek[j].cord[1];
            }
            if(direct == 1 && stek[j].cord[1]+mash<1000){ //Вверх
                stek[j].cord[1]+=mash;
            }
            if(direct == 2 && stek[j].cord[0]-mash>0){//Влево
                stek[j].cord[0]-=mash;   
            }
            if(direct == 3 && stek[j].cord[0]+mash<1000){//Вправо
                stek[j].cord[0]+=mash;
            }
            if(direct == 4 && stek[j].cord[1]-mash>0){//Вниз
                stek[j].cord[1]-=mash;
            }
            stek[j].memory[i][0]=stek[j].cord[0];
            stek[j].memory[i][1]=stek[j].cord[1];
        }
    }
}
//заглушки
void rand_way(obj * stek, int count_obj, int count_mov, int mash){
}
void Gaus(obj * stek, int count_obj, int count_mov, int mash){
}
void Chain(obj * stek, int count_obj, int count_mov, int mash){
}
int find(int id1, int id2, obj * stek, int count_obj, int count_mov, int mash){//найти расстояние
	int i, j,rast, a,b,d, x1,y1, x2,y2;
	for(i=0;i<count_obj;i++){
		if(id1 == stek[i].id){ //находит координаты указанных объектов
			x1=stek[i].cord[0];
			y1=stek[i].cord[1];
		}
		if(id2 == stek[i].id){
			x2=stek[i].cord[0];
			y2=stek[i].cord[1];
		}
	}
	printf("\nКоординаты 1 точки (%d, %d)", x1, y1);
	printf("\nКоординаты 2 точки (%d, %d)", x2, y2);
	a=x2-x1;
	b=y2-y1;
	rast=sqrt(pow(a,2)+ pow(b,2));
	return rast;
}
int main(){
    srand(time(NULL));
    int i,j,objt,x,y, chek=0, count_obj, count_mov, id, mash, choice, mov;
    obj *stek; //массив структур
    printf("\nВведите масштаб(рекоммендуется 1 к 20) 1к : "); //выбор масштаба
    scanf("%d", &mash);
    printf("\nВведите количество объектов: ");
    scanf("%d", &count_obj);
    printf("\nВведите количество движений: ");
    scanf("%d", &count_mov);
    stek = (obj*)malloc(count_obj * sizeof(obj)); //выделение памяти для массива
    for(i=0;i<count_obj;i++){
        obj temp;
        temp.id = 0; //id что бы был, потом заменим
        temp.cord[0]=-1; //задаем изначальные координаты  что бы были
        temp.cord[1]=-1;
        temp.memory = (int**)malloc(count_mov * sizeof(int*));//выделяем память для массива memmory
        for(j=0;j<count_mov;j++){
            temp.memory[j] = (int*)malloc(sizeof(int) * 2);//выделяем память для хранения координат в массиве memory
        }
        stek[i]=temp;//заполняем массив
    }
    for(i=0;i<count_obj;i++){
        printf("\nВведите ID объекта №%d ", i+1);  // Пока что id нужно вводить вручную, проверка на одинаковые значения пока не предусмотренна 
        scanf("\n%d", &id);
        chek = 0;
        for(j=0;j<count_obj;j++){
            if(id == stek[j].id)chek=1;
        }
        if(chek==0)stek[i].id = id;
        else{
            printf("\nID должен отличаться");
            i--;
        }
    }
    //пояснение за масштаб, он нужен что бы было удобно отображать на экране поле, все координаты остаются в масштабе 1к1, для правильного вычисления расстояния  
    for(i=0;i<count_obj;i++){
        x = (rand()%(1000/mash))*mash;//масштаб. В данном случае x и y это машсштабируемые координаты для отображения на экране(в структуре они все еще 1к1)
        y = (rand()%(1000/mash))*mash;//масштаб
        for(j=0;j<count_obj;j++){//выдача объектам начальных координат, одинаковые координаты не проходят
            if(x!=stek[j].cord[0] && y!=stek[j].cord[1]){
                chek=1;
            }
            else{
                chek=0;
                continue;
            }
        }
        if(chek==1){
            stek[i].cord[0] = x; //Начальные координаты
            stek[i].cord[1] = y; //Начальные координаты
            stek[i].memory[0][0]=x; //помещение их в память
            stek[i].memory[0][1]=y; //помещение их в память
        }
        else i--;
    }
    printf("\nВыберете вариант движения: 1-random, 2-Random Waypoint, 3-Gaussian-Markov, 4-Markov Chains >> "); //заготовка 
    scanf("%d", &choice);
    if(choice == 1) rando(stek,count_obj, count_mov, mash);
    else if(choice == 2) rand_way(stek,count_obj, count_mov, mash);//заготовка
    else if(choice == 3) Gaus(stek,count_obj, count_mov, mash);//заготовка
    else if(choice == 4) Chain(stek,count_obj, count_mov, mash);//заготовка
    //отрисовка поля и объектов с учетом масштаба
    for(mov=0;mov<count_mov;mov++){
		sleep(1); // задержка 1 секунда
        system("clear");
        for(i=0;i<(1000/mash);i++){
            for(j=0;j<(1000/mash);j++){
		        chek=0;
                for(objt=0;objt<count_obj;objt++){
                    if(i==((stek[objt].memory[mov][1])/mash) && j == ((stek[objt].memory[mov][0])/mash)){ //если встречается координата объекта
                        printf("0 ");
                        chek=1;
                    }
                    else if ((i!=((stek[objt].memory[mov][1])/mash) || j != ((stek[objt].memory[mov][0])/mash)) && (chek == 0)) chek = 0;
                }
                if(chek==0) printf("* "); //если объект не встретился
	    }
        printf("\n");
    	}
    }
	choice = 0;
	int id_1,id_2, rasst;
	while(choice!=2){
		printf("\n\nХотите узнать расстояние между точками?1-Da 2-Net : ");
		scanf("%d", &choice);
		if(choice == 1){
			printf("\nВведите ID 1точки: ");
			scanf("%d",&id_1);
			printf("\nВведите ID 2точки: ");
			scanf("%d",&id_2);
			rasst=find(id_1,id_2,stek,count_obj, count_mov,mash);
			printf("\n\nРасстояние между точками равно %d метров", rasst);
		}
		else if(choice == 2)printf("\nПрограмма завершена");
		else printf("\nError:Неверная команда\n");
	}
    //очищение памяти
	for(objt=0;objt<count_obj;objt++){
		for(j=0;j<count_mov;j++){
			free(stek[objt].memory[j]);
		}
		free(stek[objt].memory);
	}
	free(stek);
}

