//
//  main.cpp
//  Kmeans
//
//  Created by ychen on 2018/10/23.
//  Copyright © 2018年 ychen. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct Data{
    double x,y;
    Data(double x = 0, double y = 0){
        this->x = x;
        this->y = y;
    }
};

class Kmeans{
public:
    // training
    void run_kmeans(vector<Data> &data, int cluster_nums){
        cout << "KMeans training..." << endl;
        init(data,cluster_nums);
        get_init_kcenters();
        int interator_num;
        /*
            We will keep track of whether the assignment of data points to the clusters has changed.
            If it stops changing, we are done fitting the model
         */
        for(interator_num = 0; ; interator_num++){
            vector<int> new_data_cluster;
            update_data_cluster(new_data_cluster);
            // check whether the assignment of data points to the clusters has changed.
            if(this->data_cluster == new_data_cluster){
                cout << "Kmeans training finished after " << interator_num <<" iterations." << endl;
                break;
            }
            this->data_cluster = new_data_cluster;
            update_kcenters();
        }
        // print cluster center
        show_cluster_center();
    }
    
    int predict(Data data){
        return find_closet_cluster(data);
    }
    
private:
    int K; // cluster_nums
    int data_size; // data size
    vector<Data> dataset; // data to be cluster
    vector<int> data_cluster; // the cluster id of each data
    vector<Data> k_centers; // center of K cluster
    
    void init(vector<Data> &data, int cluster_nums){
        this->dataset = data;
        this->data_size = (int)data.size();
        this->K = cluster_nums;
        this->k_centers.clear();
        this->data_cluster.clear();
    }
    
    // random choose K data as init center
    void get_init_kcenters(){
        for(int i = 0; i < this->data_size; i++){
            if(i < this->K){
                this->k_centers.push_back(this->dataset[i]);
            }else{
                srand(time(0));
                int score = rand() % (i + 1); // generate random number from [0,i]
                if(score < K)
                    this->k_centers[score] = this->dataset[i];
            }
        }
        show_cluster_center();
    }
    
    // calculate cluster each data belongs to
    void update_data_cluster(vector<int> & data_cluster){
        for(int i = 0; i < this->data_size; i++){
            // cal distance to all center and find minimum
            data_cluster.push_back(find_closet_cluster(this->dataset[i]));
        }
    }
    
    // get cluster id the data belongs to
    int find_closet_cluster(Data &data){
        priority_queue<pair<double,int>, vector<pair<double, int>>, greater<pair<double, int>> > pq; // min heap
        // cal distance to all center and find minimum
        for(int i = 0; i < this->K; i++){
            pq.push({cal_distance(data, this->k_centers[i]),i});
        }
        return pq.top().second;
    }
    
    void update_kcenters(){
        this->k_centers.clear();
        unordered_map<int, pair<double, double>> center_pos; // accumulate x,y each cluster
        unordered_map<int, int> counter; // #points each cluster owns
        for(int i = 0; i < this->data_size; i++){
            if(center_pos.find(this->data_cluster[i]) == center_pos.end())
                center_pos[this->data_cluster[i]] = {0.0, 0.0};
            counter[this->data_cluster[i]]++;
            pair<double, double> p = center_pos[this->data_cluster[i]];
            center_pos[this->data_cluster[i]] = {p.first + this->dataset[i].x ,p.second + this->dataset[i].y};
        }
        for(int i = 0; i < this->K; i++)
            this->k_centers.push_back(Data(center_pos[i].first/counter[i], center_pos[i].second/counter[i]));
    }
    
    // calculate distance between 2 points
    double cal_distance(Data &d1, Data &d2){
        return sqrt((d1.x - d2.x) * (d1.x - d2.x) + (d1.y - d2.y)*(d1.y - d2.y));
    }
    
    void show_cluster_center(){
        cout << "cluster center:" << endl;
        for(auto &center: this->k_centers)
            cout<< center.x << "," << center.y <<endl;
    }
};

int main(int argc, const char * argv[]) {
    vector<Data> dataset;
    dataset.push_back(Data(0,5));
    dataset.push_back(Data(0,6));
    dataset.push_back(Data(1,4.5));
    dataset.push_back(Data(1,5.5));
    dataset.push_back(Data(3,5));
    dataset.push_back(Data(2,0.3));
    dataset.push_back(Data(1,1.6));
    dataset.push_back(Data(3,1));
    dataset.push_back(Data(4,0.1));
    dataset.push_back(Data(3,6.1));
    dataset.push_back(Data(1,1.1));
    dataset.push_back(Data(1,2));
    
    Kmeans kmeans;
    kmeans.run_kmeans(dataset, 2);
    cout << "predict..." << endl;
    cout << kmeans.predict(Data(2,7)) << endl;
    cout << kmeans.predict(Data(3,0.5)) << endl;
    cout << kmeans.predict(Data(1,2)) << endl;
    cout << kmeans.predict(Data(1.5,5.5)) << endl;
    return 0;
}
