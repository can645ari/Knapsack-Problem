#include <iostream>
#include <vector>
#include <fstream>
#include <clocale>

using namespace std;

// Knapsack problemini çözen fonksiyon
int knapsack(int capacity, int n, vector<int>& weights, vector<int>& values, vector<int>& selected_items) {
    // dp[i][w], i. eşyalar arasından w kapasiteli çantaya koyabileceğimiz maksimum değer
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (weights[i - 1] > w) {
                // Bu eşyayı alamıyoruz, önceki durumu alıyoruz
                dp[i][w] = dp[i - 1][w];
            }
            else {
                // Eşyayı ya alır ya almaz, değeri maksimize ediyoruz
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
        }
    }

    // Seçilen öğeleri bulmak için geriye doğru izleme
    int w = capacity;
    for (int i = n; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            // Bu eşya seçilmiştir
            selected_items[i - 1] = 1;
            w -= weights[i - 1];
        }
        else {
            // Bu eşya seçilmemiştir
            selected_items[i - 1] = 0;
        }
    }

    return dp[n][capacity]; // En son hesaplanan en iyi değeri döndürüyoruz
}

int main() {
    setlocale(LC_ALL, "Turkish");
    int K;//Çantanın kapasitesi
    int N;//toplam eşya sayısı
    vector<int> values;
    vector<int> weights;

    /* ks_19_0 / ks_50_0 / ks_100_2 / ks_500_0 / ks_10000_0 */

    ifstream file("..\\data\\ks_500_0");

    if (!file) {
        cerr << "Dosya acilamadi" << endl;
        return -1;
    }
    file >> N;
    file >> K;

    int value, weight;
    while (file >> value >> weight) {
        values.push_back(value);
        weights.push_back(weight);
    }

    vector<int> selected_items(N, 0);//başlangıçta tüm itemler seçilmedi olarak işaretleniyor

    int max_value = knapsack(K, N, weights, values, selected_items);

    cout << max_value << endl;

    //    cout << "Seçilen öğeler: " << endl;
    for (int i = 0; i < N; ++i) {
        cout << selected_items[i] << " ";
    }
    cout << endl;

    return 0;
}