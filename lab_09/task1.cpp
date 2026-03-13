#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Activity {
    int start;
    int finish;
};

bool compare(Activity a, Activity b) {
    return a.finish < b.finish;
}

int main() {

    vector<Activity> activities;

    activities.push_back((Activity){1,5});
    activities.push_back((Activity){3,8});
    activities.push_back((Activity){4,9});
    activities.push_back((Activity){7,10});
    activities.push_back((Activity){9,12});
    activities.push_back((Activity){11,15});
    activities.push_back((Activity){13,17});
    activities.push_back((Activity){15,18});
    activities.push_back((Activity){8,11});
    activities.push_back((Activity){6,9});
    activities.push_back((Activity){5,12});
    activities.push_back((Activity){10,13});
    activities.push_back((Activity){2,4});

    int n = activities.size();

    sort(activities.begin(), activities.end(), compare);

    cout << "Відсортовані заявки:\n";

    for(int i = 0; i < n; i++) {
        cout << "(" << activities[i].start << ", " << activities[i].finish << ")" << endl;
    }

    cout << "\nОбрані заявки:\n";

    Activity last = activities[0];
    cout << "(" << last.start << ", " << last.finish << ")" << endl;

    int count = 1;

    for(int i = 1; i < n; i++) {
        if(activities[i].start >= last.finish) {
            cout << "(" << activities[i].start << ", " << activities[i].finish << ")" << endl;
            last = activities[i];
            count++;
        }
    }

    cout << "\nМаксимальна кількість заявок: " << count << endl;

    return 0;
}