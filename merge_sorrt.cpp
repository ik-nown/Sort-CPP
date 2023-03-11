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
void merge(vector<double> &a, int start, int mid, int end){
    int n1 = mid - start + 1; // Số phần tử mảng con trái 
                                    // + 1 là do lưu thêm phần tử ở vị trí mid
    int n2= end-mid;          // Số phần tử mảng con phải
    int left[n1]; int right[n2];  // Khai báo hai mảng trung gian
    // Copy giữ liệu từ mảng chính ra hai mảng con
    for(int x=0; x<n1; x++) left[x] = a[start+x]; 
    for(int y=0; y<n2; y++) right[y] = a[mid+1+y];
    
    int i=0, j=0;     // Khai báo hai biến chạy để duyệt mảng con
    int k=start;     // Lưu k làm vị trí bắt đầu của mảng chính,
    
    while(i<n1 && j<n2){    // Trong khi cả hai mảng con chưa hết phần tử
        if(left[i]>=right[j]){   // Nếu phần tử mảng con trái >= mảng con phải
            a[k]=right[j];   // Điển phần tử mảng con phải vào mảng chính
            j++;             // xét phần tử tiếp theo của mảng right
        }
        else{               // Ngược lại tức là left[i] < right[j]
            a[k]=left[i];
            i++;
        }
        k++;              // Tăng index của mảng chính, mỗi lần lặp sẽ tìm được 1 phần tử thích hợp
    }
    
        // Sau vòng lặp trên, 1 trong 2 mảng đã duyệt hết phần tử, hoặc cả hai cùng hết
    while(j<n2){      // Nếu mảng right chưa hết, mảng left đã hết
        a[k]=right[j]; // Cho toàn bộ các phần tử còn lại vào mảng chính
        k++;
        j++;    
    }
    while(i<n1){     // Nếu mảng left chưa hết, mảng right hết
        a[k]= left[i];
        k++;
        i++;    
    }
}
void mergeSort(vector<double> &a, int first, int end){
    int t;    //  biến để lưu vị trí chia đôi mảng
    if(first<end){              // Nếu mảng còn ít nhất 1 phần tử
        t=(first+end)/2;    // Chia đôi mảng
        mergeSort(a,first,t);   // Đệ quy mảng trái
        mergeSort(a,t+1,end);   // Đệ quy mảng phải
        merge(a,first,t,end);   // Trộn hai mảng lại
    }
    else    // Mảng < 1 phần tử sẽ dừng đệ quy
        return;
}
void tang(vector<double> &out)
{
    mergeSort(out,0,si-1);
}
int main()
{
    clock_t start, end;
    double duration;
    std::ofstream output("out.txt");
    if (!output.is_open())
    {
        std::cout << "Không thể mở file out.txt!" << std::endl;
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
