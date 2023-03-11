#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <time.h>
#include <sstream>
#include <math.h>
#define si 1000000
#define r 10
using namespace std;
void duyet(vector<string> &f)
{
    std::ifstream inFile("botest.txt"); // mở file input.txt để đọc
    // if (!inFile.is_open())
    // {
    //     std::cout << "Không thể mở file!" << std::endl;
    //     return 0;
    // }
    string line;
    while (getline(inFile, line))
    {                      // cout<<line;
        f.push_back(line); // Lưu từng dòng như một phần tử vào vector lines.
    }
    inFile.close(); // đóng file input
}
vector<double> preprocess1(vector<double> &day, string s, int cnt)
{
    long column = 0;
    int i = 0, j = si - 1;
    vector<string> temp;
    stringstream ss(s);
    while (ss.good() && column < si)
    {
        string sub;
        getline(ss, sub, ',');
        temp.push_back(sub);
        column++;
    } // loại bỏ dấu phẩy và đưa vào vector temp
    string s1=temp[i]; s1.erase(i,1); temp[i]=s1;
    string s2=temp[j]; s2.erase(s2.size()-2,1); temp[j]=s2;

    for (int i = 0; i < si; i++)
    {
        string x = temp[i];
        stringstream s(x);
        double a;
        s >> a;
        a=round(a*100)/100;
        day[(cnt * (si - 1) + i)] =a; //làm tròn 2 chữ số thập phân.
    } // lấy từng số từ temp ra xử lí và lưu vào day.
    return day;
} // hàm xử lí một dòng và trả về day đã được cập nhật thêm 1 dòng.
vector<double> preprocess(vector<string> f, vector<double> &day) // col=si
{
    preprocess1(day, f.at(0), 0);
    preprocess1(day, f.at(1), 1);
    preprocess1(day, f.at(2), 2);
    preprocess1(day, f.at(3), 3);
    preprocess1(day, f.at(4), 4);
    preprocess1(day, f.at(5), 5);
    preprocess1(day, f.at(6), 6);
    preprocess1(day, f.at(7), 7);
    preprocess1(day, f.at(8), 8);
    preprocess1(day, f.at(9), 9);
    return day;
} // gọi hàm sử lí từng dòng và trả về day(10tr phần tử)
void swap(int &a, int &b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}
int partition(vector<double> &a, int low, int high){
    int pivot = a[high];     // Chọn pivot là phần tử cuối cùng
    int right = high-1, left = low;    // Chọn left, right
    while(true){                         // Trong khi còn đúng (left < right)
        while(left<=right && a[left]<pivot) left++;     // Tìm left thích hợp
        while(right>=left && a[right]>pivot) right--;   // Tìm right thích hợp
        if(left>=right)              // left >= right dừng
            break;
        swap(a[left], a[right]);     // Đổi chỗ
        left++;                     // Xét phần tử tiếp theo
        right--;
    }
    swap(a[left], a[high]);            // Đổi chỗ pivot về giữa mảng
    return left;                       // Trả về vị trí của pivot  
}

void quickSort(vector<double> &a, int low, int high){
    if(low < high)  //Mảng có nhiều hơn 0 phần tử
    {
        int pivot = partition(a, low, high);  // Chia đôi mảng
        quickSort(a,low, pivot-1);           // Đệ quy bên trái
        quickSort(a, pivot+1, high);         // Đệ quy bên phải
    }
}
void tang(vector<double> &out)
{   
    quickSort(out,0,si-1);
}

int main()
{
    clock_t start, end;
    double duration;
    std::ofstream output("out.txt");
    if (!output.is_open())
    {
        std::cout << "Không thể mở file output.txt!" << std::endl;
        return 0;
    }
    vector<string> lines;
    duyet(lines);
    // cout<<lines.size();
    vector<double> day;
    day.resize(si * r);
    preprocess(lines, day); //trả về dãy đã xử lí xong.
    for (int i = 0; i < r; i++)
    {
        vector<double> out; //vector lưu mỗi lần sort.
        out.resize(si);
        for (int j = 0; j < si; j++)
        {
            out[j] = day[((i * (si - 1)) + j)];
        }
        // if(i=0) tang(out);
        // else if(i=1) giam(out);
        start=clock();
            tang(out);
        end=clock();
        duration=double(end-start)/ CLOCKS_PER_SEC;
        output<<duration<<" ";
        out.clear();
    }
    output.close(); // đóng file output
    return 0;
}
