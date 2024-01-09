#include <bits/stdc++.h>
using namespace std;

class Registration
{
private:
    string first_name;
    string last_name;
    int age;
    string gender;

public:
    void set(string first_name, string last_name, int age, string gender)
    {
        this->first_name = first_name;
        this->last_name = last_name;
        this->age = age;
        this->gender = gender;
    }

    void get()
    {
        cout << "Name = " << first_name << " " << last_name << endl;
        cout << "Age = " << age << endl;
        cout << "Gender = " << gender << endl;
    }
};

class RoomAllocation
{
public:
    int cnt;
    string type;
    vector<int> room_num;

    void set(int cnt, string type, vector<int> room_num)
    {
        this->cnt = cnt;
        this->type = type;
        this->room_num = room_num;
    }

    void get()
    {
        cout << type << " :- " << cnt;
        if (cnt == 0)
        {
            cout << endl;
            return;
        }
        cout << " (Room number :- ";
        for (auto i : room_num)
        {
            cout << i << " ";
        }
        cout << ")" << endl;
    }
};

class EnjoymentFeatures
{
private:
    int ind;
    string name;
    int ct;

public:
    void set(int ind, string name, int ct)
    {
        this->ind = ind;
        this->name = name;
        this->ct = ct;
    }

    void get()
    {
        cout << ind << ". " << name << "(Cost - Rs." << ct << ")" << endl;
    }
};

class Food
{
public:
    int ind;
    string name;
    int ct;

    void set(int ind, string name, int ct)
    {
        this->ind = ind;
        this->name = name;
        this->ct = ct;
    }

    void get()
    {
        cout << ind << ". " << name << "(Cost - Rs." << ct << ")" << endl;
    }
};

int dijkstra(vector<vector<int>> &vec, int ver, int edges, int src, int dest)
{
    unordered_map<int, list<pair<int, int>>> adj;
    for (int i = 0; i < edges; i++)
    {
        int u = vec[i][0];
        int v = vec[i][1];
        int w = vec[i][2];

        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    vector<int> dist(ver);

    for (int i = 0; i < ver; i++)
    {
        dist[i] = INT_MAX;
    }

    set<pair<int, int>> st;

    dist[src] = 0;
    st.insert(make_pair(0, src));

    while (!st.empty())
    {
        auto top = *st.begin();

        int nodeDist = top.first;
        int topNode = top.second;

        st.erase(st.begin());

        for (auto i : adj[topNode])
        {
            if (nodeDist + i.second < dist[i.first])
            {
                auto record = st.find(make_pair(dist[i.first], i.first));

                if (record != st.end())
                {
                    st.erase(record);
                }

                dist[i.first] = nodeDist + i.second;
                st.insert(make_pair(dist[i.first], i.first));
            }
        }
    }

    return dist[dest];
}

int main()
{
    int start;
    cout << "Let's start our day, press 1" << endl;
    cin >> start;

    // when end become 0 we have to stop there else we want to continue then end = 1

    while (1)
    {
        if (start == 0)
        {
            cout << "It's break time now. " << endl;
            break;
        }

        // for calculating total cost
        long long int cost = 0;

        cout << "Welcome to our resort, Sir/Mam." << endl;
        cout << "Now, you are in the resort's booking section, In the resort's booking section, provide all the needed information to book your stay now." << endl;

        // User Registration and Authentication
        cout << "Your first name - ";
        string led_first_name;
        cin >> led_first_name;

        cout << "Your last name - ";
        string led_last_name;
        cin >> led_last_name;

        cout << "Your age - ";
        int led_age;
        cin >> led_age;

        cout << "Your gender - ";
        string led_gender;
        cin >> led_gender;

        cout << "Your email_id - ";
        string led_email;
        cin >> led_email;

        cout << "Your phone number - ";
        string led_phone_num;
        cin >> led_phone_num;

        cout << "number of people - ";
        int total_people;
        cin >> total_people;

        cout << "Please enter the details of all the people : -" << endl;

        Registration *all_detail = new Registration[total_people];

        for (int i = 0; i < total_people; i++)
        {
            string fir_nm;
            cout << "Fisrt Name - ";
            cin >> fir_nm;
            string la_nm;
            cout << "Last Name - ";
            cin >> la_nm;
            int ag;
            cout << "Age - ";
            cin >> ag;
            string gen;
            cout << "Gender - ";
            cin >> gen;

            all_detail[i].set(fir_nm, la_nm, ag, gen);
        }

        cout << endl;

        cout << "Presenting your pertional information on one place :- " << endl;

        cout << "Person Name :- " << led_first_name << " " << led_last_name << endl;
        cout << "Age :- " << led_age << endl;
        cout << "Gender :- " << led_gender << endl;
        cout << "Email-id :- " << led_email << endl;
        cout << "Phone Number :- " << led_phone_num << endl;
        cout << "Total number of people(except him/her) :- " << total_people << endl;

        for (int i = 0; i < total_people; i++)
        {
            all_detail[i].get();
        }

        cout << endl;

        // Room availability

        // roomno,check_in,check_out
        unordered_map<int, pair<string, string>> single_bed_nonac;
        vector<pair<bool, int>> single_bed_nonac_room(50);

        unordered_map<int, pair<string, string>> single_bed_ac;
        vector<pair<bool, int>> single_bed_ac_room(50);

        unordered_map<int, pair<string, string>> double_bed_nonac;
        vector<pair<bool, int>> double_bed_nonac_room(50);

        unordered_map<int, pair<string, string>> double_bed_ac;
        vector<pair<bool, int>> double_bed_ac_room(50);

        for (int i = 0; i < 50; i++)
        {
            single_bed_nonac_room[i] = {false, i};
            single_bed_ac_room[i] = {false, i};
            double_bed_nonac_room[i] = {false, i};
            double_bed_nonac_room[i] = {false, i};
        }

        // Mark some rooms as already occupied

        single_bed_nonac_room[0] = {true, 0};
        single_bed_nonac[0] = make_pair(12 - 5 - 2023, 25 - 5 - 2023);
        single_bed_nonac_room[3] = {true, 3};
        single_bed_nonac[3] = make_pair(12 - 5 - 2023, 25 - 5 - 2023);
        single_bed_nonac_room[5] = {true, 5};
        single_bed_nonac[5] = make_pair(12 - 5 - 2023, 25 - 5 - 2023);

        single_bed_ac_room[0] = {true, 0};
        single_bed_ac[0] = make_pair(12 - 5 - 2023, 25 - 5 - 2023);
        single_bed_ac_room[5] = {true, 5};
        single_bed_ac[5] = make_pair(12 - 5 - 2023, 25 - 5 - 2023);

        double_bed_nonac_room[0] = {true, 0};
        double_bed_nonac[0] = make_pair(12 - 5 - 2023, 25 - 5 - 2023);
        double_bed_nonac_room[3] = {true, 3};
        double_bed_nonac[3] = make_pair(12 - 5 - 2023, 25 - 5 - 2023);

        double_bed_ac_room[0] = {true, 0};
        double_bed_ac[0] = make_pair(12 - 5 - 2023, 25 - 5 - 2023);
        double_bed_ac_room[2] = {true, 2};
        double_bed_ac[2] = make_pair(12 - 5 - 2023, 25 - 5 - 2023);

        sort(single_bed_nonac_room.begin(), single_bed_nonac_room.end());
        sort(single_bed_ac_room.begin(), single_bed_ac_room.end());
        sort(double_bed_nonac_room.begin(), double_bed_nonac_room.end());
        sort(double_bed_ac_room.begin(), double_bed_ac_room.end());

        // map the cost with index number,room type and cost

        unordered_map<int, pair<string, int>> room_cost;

        room_cost[1] = make_pair("Single bed non ac rooms", 800);
        room_cost[2] = make_pair("Single bed ac rooms", 1300);
        room_cost[3] = make_pair("Double bed non ac rooms", 1100);
        room_cost[4] = make_pair("Double bed ac rooms", 2000);

        cout << "We have following type of rooms (Given cost for per day, without GST) :- " << endl;
        for (int i = 1; i <= 4; i++)
        {
            cout << i << ". " << room_cost[i].first << "(cost - Rs." << room_cost[i].second << ")" << endl;
        }

        cout << endl;

        cout << "Please provide me the data related to room type and number of rooms :- " << endl;

        RoomAllocation room_allocate[4];

        for (int j = 1; j <= 4; j++)
        {
            cout << "Number of " << room_cost[j].first << " - ";
            vector<int> temp_room_num;
            int a;
            cin >> a;

            int cnt_room = 0;
            for (int i = 0; i < a; i++)
            {
                if ((j == 1 && single_bed_nonac_room[i].first) || (j == 2 && single_bed_ac_room[i].first) || (j == 3 && double_bed_nonac_room[i].first) || (j == 4 && double_bed_ac_room[i].first))
                {
                    cout << "We have only " << cnt_room << " vacant " << room_allocate[j].type << ", So please enter value less than or equal to " << cnt_room << " - ";

                    while (a > cnt_room)
                    {
                        int temp;
                        cin >> temp;
                        a = temp;
                    }
                    break;
                }
                else
                {
                    cnt_room++;
                }
            }

            for (int i = 0; i < a; i++)
            {
                if (j == 0)
                    temp_room_num.push_back(single_bed_nonac_room[i].second);
                else if (j == 1)
                    temp_room_num.push_back(single_bed_ac_room[i].second);
                else if (j == 2)
                    temp_room_num.push_back(double_bed_nonac_room[i].second);
                else
                    temp_room_num.push_back(double_bed_ac_room[i].second);
            }

            cost += (a * 1LL * (room_cost[j].second));
            room_allocate[j - 1].set(a, "Single bed ac room", temp_room_num);
        }

        cout << "We have listed all the booked room below :- " << endl;
        for (int i = 0; i < 4; i++)
        {
            room_allocate[i].get();
        }

        cout << endl;

        cout << "The total cost for room booking is (without GST) :- Rs." << cost << endl;

        if (cost <= 1000)
        {
            cout << "There will be no GST so total cost will be :- Rs." << cost << endl;
        }
        else if (cost > 1000 && cost <= 75000)
        {
            long long int temp = cost + ((cost * 1LL * 12) / 100);
            cost = temp;
            cout << "There will be 12% GST so total cost will be :- Rs." << cost << endl;
        }
        else
        {
            long long int temp = cost + ((cost * 1LL * 18) / 100);
            cost = temp;
            cout << "There will be 18% GST so total cost will be :- Rs." << cost << endl;
        }

        long long int temp_roombook_cost = cost;

        cout << endl;

        // Enjoyment Features

        cout << "In our resort, the available enjoyment features are listed below(Cost given as per day, without GST) :- " << endl;
        cout << "1. Swimming Pool(Cost - Rs.2000)" << endl;
        cout << "2. Tennis Courts(Cost - Rs.300)" << endl;
        cout << "3. Night Club(Entry Fee - Rs.500 per person)" << endl;
        cout << "4. Spa Services(Cost - Rs.2000 per person)" << endl;
        cout << "5. Park(Free)" << endl;
        cout << "6. Kids' Club(Entry Fee - Rs.300 per kid)" << endl;
        cout << "7. Outdoor Recreational Activities(Cost - Rs.400 per person)" << endl;
        cout << "8. Live Music(Entry Fee Rs.200 per person)" << endl;
        cout << "9. Water Sports(Cost - Rs.300 per sport)" << endl;
        cout << "10. Cultural Experiences(Entry Fee Rs.200 per person)" << endl;

        cout << endl;

        // map all the enjoyment features with index number, name and cost
        unordered_map<int, pair<string, int>> feature_cost;

        feature_cost[1] = make_pair("Swimming Pool", 2000);
        feature_cost[2] = make_pair("Tennis Courts", 300);
        feature_cost[3] = make_pair("Night Club", 400);
        feature_cost[4] = make_pair("Spa Services", 2000);
        feature_cost[5] = make_pair("Park", 0);
        feature_cost[6] = make_pair("Kid's Club", 300);
        feature_cost[7] = make_pair("Outdoor Recreational Activities", 400);
        feature_cost[8] = make_pair("Live Music", 200);
        feature_cost[9] = make_pair("Water Sports", 300);
        feature_cost[10] = make_pair("Cultural Experiences", 200);

        cout << "We possess the shortest path data for the specific spots you seek." << endl;

        vector<vector<int>> path;
        int vertex = 10;
        int edges = 14;

        path.push_back({1, 4, 200});
        path.push_back({1, 6, 500});
        path.push_back({1, 9, 300});
        path.push_back({2, 5, 200});
        path.push_back({2, 7, 600});
        path.push_back({2, 9, 500});
        path.push_back({3, 4, 100});
        path.push_back({3, 6, 100});
        path.push_back({3, 8, 200});
        path.push_back({5, 7, 700});
        path.push_back({6, 8, 300});
        path.push_back({6, 10, 300});
        path.push_back({8, 10, 200});
        path.push_back({9, 10, 900});

        cout << "Enter the spots index number between them to find the shortest path :- " << endl;
        int sp1, sp2;
        cout << "First spot index number :- ";
        cin >> sp1;
        cout << "Second spot index number :- ";
        cin >> sp2;

        cout << "The shortest path between " << feature_cost[sp1].first << " and " << feature_cost[sp2].first << " is " << dijkstra(path, vertex, edges, sp1, sp2) << " meters." << endl;

        cout << "If you want to about more spots than enter 1 and then spots index number else enter 0 :- ";

        while (1)
        {
            int morecnt;
            cin >> morecnt;
            if (morecnt == 1)
            {
                cout << "Enter the spot index number between them to find the shortest path :- "<<endl;
                int sp3, sp4;
                cout << "First spot index number :- ";
                cin >> sp3;
                cout << "Second spot index number :- ";
                cin >> sp4;
                cout << "The shortest path between " << feature_cost[sp3].first << " and " << feature_cost[sp4].first << " is " << dijkstra(path, vertex, edges, sp3, sp4) << " meters." << endl;
            }
            else
            {
                break;
            }
        }

        cout << endl;

        cout << "Please enter how many enjoyment features you want to enroll(should be less than equal to 10) - ";
        int feature_num;
        cin >> feature_num;

        EnjoymentFeatures *seleted_features = new EnjoymentFeatures[feature_num];

        long long int temp_fea_cost = 0; // will store cost of enjoyment features

        cout << "Kindly indicate the chosen enjoyment feature one by one :- " << endl;
        for (int i = 0; i < feature_num; i++)
        {
            int b1;
            cout << "Index number - ";
            cin >> b1;

            if (b1 > 10)
            {
                while (b1 > 10)
                {
                    int temp;
                    cout << "Please enter index from 1 to 10 (as already described) - ";
                    cin >> temp;
                    b1 = temp;
                }
            }

            string tmp = feature_cost[b1].first;
            int ct = feature_cost[b1].second;

            if ((b1 == 3) || (b1 == 4) || (b1 >= 6 && b1 <= 10))
            {
                cout << "Please enter count also (as mentioned per person or sport) - ";
                int cnt;
                cin >> cnt;

                temp_fea_cost += (cnt * 1LL * ct);
            }
            else
            {
                temp_fea_cost += ct;
            }

            seleted_features[i].set(i + 1, tmp, ct);
        }

        cout << endl;

        cout << "Your selected features (with cost) are :- " << endl;

        for (int i = 0; i < feature_num; i++)
        {
            seleted_features[i].get();
        }

        cout << endl;

        cout << "The cost for Enjoyment Features (without GST) is :- Rs." << temp_fea_cost << endl;

        if (temp_fea_cost <= 1000)
        {
            cout << "There will be no GST so total Enjoyment Features cost will be :- Rs." << temp_fea_cost << endl;
        }
        else if (temp_fea_cost > 1000 && temp_fea_cost <= 75000)
        {
            long long int temp = temp_fea_cost + ((temp_fea_cost * 1LL * 12) / 100);
            temp_fea_cost = temp;
            cout << "There will be 12% GST so total Enjoyment Features cost will be :- Rs." << temp_fea_cost << endl;
        }
        else
        {
            long long int temp = temp_fea_cost + ((temp_fea_cost * 1LL * 18) / 100);
            temp_fea_cost = temp;
            cout << "There will be 18% GST so total Enjoyment Features cost will be :- Rs." << temp_fea_cost << endl;
        }

        cost += temp_fea_cost;

        cout << "Now the total cost including room booking and selected features is :- Rs." << cost << endl;

        cout << endl;

        // breakfast

        unordered_map<int, pair<string, int>> breakfast_cost;

        breakfast_cost[1] = make_pair("Masals Dosa", 60);
        breakfast_cost[2] = make_pair("Poha", 60);
        breakfast_cost[3] = make_pair("Upma", 50);
        breakfast_cost[4] = make_pair("Al00 Paratha", 50);
        breakfast_cost[5] = make_pair("Idli with Sambar and Chutney", 50);
        breakfast_cost[6] = make_pair("Vada Pav", 40);
        breakfast_cost[7] = make_pair("Dhokla", 30);
        breakfast_cost[8] = make_pair("Chole Bhature", 70);
        breakfast_cost[9] = make_pair("Puri Bhaji", 50);
        breakfast_cost[10] = make_pair("Jalebi with Rabri", 70);

        cout << "Our breakfast menu is listed below :- " << endl;
        for (int i = 1; i <= 10; i++)
        {
            cout << i << ". " << breakfast_cost[i].first << "(Cost - Rs." << breakfast_cost[i].second << ")" << endl;
        }

        cout << endl;

        int for_breakfast;

        cout << "If you want to order for breakfast than press 1 else press 0." << endl;
        cin >> for_breakfast;

        int breakfast_quan;
        Food *selected_breakfast = new Food[breakfast_quan];
        long long temp_bf_cost = 0;
        if (for_breakfast == 1)
        {
            cout << "How many types of breakfast do you want? :- ";
            cin >> breakfast_quan;

            for (int i = 0; i < breakfast_quan; i++)
            {
                int ind;
                cout << "Index number(1-10) - ";
                cin >> ind;

                int quan;
                cout << "Quantity of " << breakfast_cost[ind].first << " - ";
                cin >> quan;

                selected_breakfast[i].set(i + 1, breakfast_cost[ind].first, breakfast_cost[ind].second);
                temp_bf_cost += quan * 1LL * breakfast_cost[ind].second;
            }

            cout << endl;
            cout << "Your ordered Breakfast is listed below :- " << endl;

            for (int i = 0; i < breakfast_quan; i++)
            {
                selected_breakfast[i].get();
            }

            cout << endl;

            cout << "The total cost of breakfast(without GST) is :- " << temp_bf_cost << endl;

            cost += temp_bf_cost;
            cout << "Now the total cost including room booking, selected features and breakfast is :- Rs." << cost << endl;
        }

        cout << endl;

        // print all the information on one place
        cout << "Now, all the information is consolidated in one place along with the total cost." << endl;

        cout << "Person Name :- " << led_first_name << " " << led_last_name << endl;
        cout << "Age :- " << led_age << endl;
        cout << "Gender :- " << led_gender << endl;
        cout << "Email-id :- " << led_email << endl;
        cout << "Phone Number :- " << led_phone_num << endl;
        cout << "Total number of people(except him/her) :- " << total_people << endl;

        for (int i = 0; i < total_people; i++)
        {
            all_detail[i].get();
        }

        cout << endl;

        cout << "We have listed all the booked room below :- " << endl;
        for (int i = 0; i < 4; i++)
        {
            room_allocate[i].get();
        }

        cout << endl;

        cout << "Room booking cost :- " << temp_roombook_cost << endl;

        cout << endl;

        cout << "Your selected features (with cost) are :- " << endl;

        for (int i = 0; i < feature_num; i++)
        {
            seleted_features[i].get();
        }

        cout << endl;

        cout << "The cost for Enjoyment Features is :- Rs." << temp_fea_cost << endl;

        if (for_breakfast == 1)
        {
            cout << "Your ordered Breakfast is listed below :- " << endl;

            for (int i = 0; i < breakfast_quan; i++)
            {
                selected_breakfast[i].get();
            }
            cout << endl;
            cout << "The cost for breakfast is :- Rs." << temp_bf_cost << endl;
        }

        cout << "Total cost :- Rs." << cost << endl;

        cout << endl;

        int notice_ke_liye;
        cout << "After completing your payment,press 1." << endl;
        cin >> notice_ke_liye;

        cout << endl;

        // review
        cout << "We are requesting you to rate our services(from 0-10) :- " << endl;

        int staff_rate;
        cout << "Our staff - ";
        cin >> staff_rate;

        if (staff_rate < 5)
        {
            string reviews;
            cout << "Kindly provide suggestions to enhance our rating.(When you done with your review please click on enter)";
            getline(cin, reviews);
        }

        int room_rate;
        cout << "Rooms condition - ";
        cin >> room_rate;

        if (room_rate < 5)
        {
            string reviews;
            cout << "Kindly provide suggestions to enhance our rating.(When you done with your review please click on enter)";
            getline(cin, reviews);
        }

        int facility_rate;
        cout << "Other facilities - ";
        cin >> facility_rate;

        if (facility_rate < 5)
        {
            string reviews;
            cout << "Kindly provide suggestions to enhance our rating.(When you done with your review please click on enter)";
            getline(cin, reviews);
        }

        cout << "Thanks for your reviews Sir/Mam. We are happy to help you." << endl;

        int end;
        cout << "Let's continue our day, press 1 for being continue and press 0 for a break." << endl;
        cin >> end;
        start = end;
    }

    return 0;
}
