#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Simulace round-robin přiřazení úloh
int simulateRoundRobin(const vector<char>& batch) {
    int timeCore0 = 0, timeCore1 = 0, timeCore2 = 0;
    // Přiřazení probíhá cyklicky: index 0 -> core0, 1 -> core1, 2 -> core2, 3 -> core0, atd.
    for (size_t i = 0; i < batch.size(); i++) {
        char task = batch[i];
        int t = 0;
        int core = i % 3; // 0: Cortex-X2, 1: Cortex-A710, 2: Cortex-A510
        if(core == 0) { 
            // Vysoce výkonné jádro – ideální pro H
            t = (task == 'H') ? 1 : 2;
            timeCore0 += t;
        }
        else if(core == 1) {
            // Středně výkonné jádro – ideální pro M
            t = (task == 'M') ? 1 : 2;
            timeCore1 += t;
        }
        else { // core == 2
            // Nízkovýkonné jádro – ideální pro L
            t = (task == 'L') ? 1 : 2;
            timeCore2 += t;
        }
    }
    // Doba zpracování dávky je dána nejdelší frontou (práce probíhá paralelně)
    return max({timeCore0, timeCore1, timeCore2});
}

// Globální proměnná pro uložení nejlepšího (minimálního) výsledku v rekurzi
int bestTime;

// Rekurzivní funkce pro optimální přiřazení úloh ke třem jádrům
void recOptimal(const vector<char>& batch, int i, int time0, int time1, int time2) {
    if(i == batch.size()) {
        int currentMax = max({time0, time1, time2});
        if(currentMax < bestTime) bestTime = currentMax;
        return;
    }
    char task = batch[i];
    
    // Přiřaď úlohu do jádra 0 (Cortex-X2, ideální pro H)
    int add0 = (task == 'H') ? 1 : 2;
    if(max({time0 + add0, time1, time2}) < bestTime)
        recOptimal(batch, i + 1, time0 + add0, time1, time2);
    
    // Přiřaď úlohu do jádra 1 (Cortex-A710, ideální pro M)
    int add1 = (task == 'M') ? 1 : 2;
    if(max({time0, time1 + add1, time2}) < bestTime)
        recOptimal(batch, i + 1, time0, time1 + add1, time2);
    
    // Přiřaď úlohu do jádra 2 (Cortex-A510, ideální pro L)
    int add2 = (task == 'L') ? 1 : 2;
    if(max({time0, time1, time2 + add2}) < bestTime)
        recOptimal(batch, i + 1, time0, time1, time2 + add2);
}

// Funkce, která pro danou dávku spočítá optimální dobu zpracování
int simulateOptimal(const vector<char>& batch) {
    bestTime = INT_MAX;
    recOptimal(batch, 0, 0, 0, 0);
    return bestTime;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int totalTasks;
    cin >> totalTasks;
    
    vector<char> tasks(totalTasks);
    for (int i = 0; i < totalTasks; i++) {
        cin >> tasks[i];
    }
    
    int totalTimeRoundRobin = 0;
    int totalTimeOptimal = 0;
    
    // Zpracování úloh po dávkách po 8 úlohách (poslední dávka může být menší)
    for (size_t i = 0; i < tasks.size(); i += 8) {
        vector<char> batch;
        for (size_t j = i; j < i + 8 && j < tasks.size(); j++) {
            batch.push_back(tasks[j]);
        }
        totalTimeRoundRobin += simulateRoundRobin(batch);
        totalTimeOptimal += simulateOptimal(batch);
    }
    
    cout << "Round-robin simulation time: " << totalTimeRoundRobin << "\n";
    cout << "Optimal scheduling simulation time: " << totalTimeOptimal << "\n";
    
    return 0;
}
