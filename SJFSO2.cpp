#include <iostream>
#include <iomanip>
using namespace std;

#define N 10

int mtx[N][6];
double sumta = 0.0, sumwait = 0.0;  //total turnaround time dan total waiting time

//fungsi swap elemen matriks
void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}
//fungsi untuk mengurutkan process berdasarkan arrival time
void sortbyarrival(int n, int mtx[][6]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n-i-1; j++){
            if(mtx[j][1] > mtx[j+1][1]){
                for(int k=0; k<6; k++){
                    swap(mtx[j][k], mtx[j+1][k]);
                }
            }
        }
    }
}
//fungsi untuk mengurutkan process berdasarkan burst time
//dg kondisi jika arrival timenya sama
void sortbyburst(int n, int mtx[][6]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n-i-1; j++){
            if(mtx[j][1] == mtx[j+1][1]){
                if(mtx[j][2] > mtx[j+1][2]){
                    for(int k=0; k<6; k++){
                        swap(mtx[j][k], mtx[j+1][k]);
                    }
                }
            }
        }
    }
}
/*| pid | arrival | burst | waiting | turnaround | completion |*/
//fungsi unutk menghitung waiting, turnaround, completion time
void counttime(int n, int mtx[][6]){
    int completion, burst, x;
    mtx[0][5] = mtx[0][1] + mtx[0][2];          //completion time
    mtx[0][4] = mtx[0][5] - mtx[0][1];          //turnaround time
    mtx[0][3] = mtx[0][4] - mtx[0][2];          //waiting time

    for(int i=1; i<n; i++){
        completion = mtx[i-1][5];
        burst = mtx[i][2];
        for(int j=i; j<n; j++){
            if(completion >= mtx[j][1] && burst >= mtx[j][2]){
                burst = mtx[j][2];
                x = j;
            }
        }
        mtx[x][5] = completion + mtx[x][2];
        mtx[x][4] = mtx[x][5] - mtx[x][1];
        mtx[x][3] = mtx[x][4] - mtx[x][2];
        for(int j=0; j<6; j++){
            swap(mtx[x][j], mtx[i][j]);
        }
    }
}

int main(){
    int n;

	cout<<"Enter number of Process: ";
	cin>>n;
	cout<<"-------------------------------------------\n";
	for(int i=0; i<n; i++){
		cout<<"Process ["<<i+1<<"]\n";
		cout<<"Enter Process Id: ";
		cin>>mtx[i][0];
		cout<<"Enter Arrival Time: ";
		cin>>mtx[i][1];
		cout<<"Enter Burst Time: ";
		cin>>mtx[i][2];
	}
	cout<<"-------------------------------------------\n";
	cout<<"\nProcess ID\tArrival Time\tBurst Time\n";
	for(int i=0; i<n; i++){
		cout<<mtx[i][0]<<"\t\t"<<mtx[i][1]<<"\t\t"<<mtx[i][2]<<"\n";
	}
    cout<<"\n-------------------------------------------\n";

    sortbyarrival(n, mtx);
    sortbyburst(n, mtx);
	counttime(n, mtx);

    for(int i=0; i<n;i++){
        sumwait += mtx[i][3];
        sumta += mtx[i][4];
    }

	cout<<"\n\n---SJF Result---\n";
	cout<<"--------------------------------------------------------------------------------\n";
	cout<<"\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
	for(int i=0; i<n; i++){
        cout<<mtx[i][0]<<"\t\t"<<mtx[i][1]<<"\t\t"<<mtx[i][2]<<"\t\t";
		cout<<mtx[i][3]<<"\t\t"<<mtx[i][4]<<"\n";
	}
	cout<<"\n--------------------------------------------------------------------------------\n";
	cout<<fixed<<setprecision(2);
	cout<<"\nAverage Waiting Time : "<<sumwait/(double)n<<"\n";
	cout<<"Average Turnaround Time : "<<sumta/(double)n<<"\n";
    return 0;
}