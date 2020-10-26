#include <bits/stdc++.h>
using namespace std;

#define FORu(i, start, n) for (ll i = start; i < (ll)(n); i++)
#define FORd(i, start, n) for (ll i = start; i > (ll)(n); i--)
#define FORa(vec) for (auto x : vec) cout << x << " ";
#define pb push_back
#define pf pop_front
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,string> P;

bool isStraight(P pHand[5]){
    bool ans = true;
    for(int i = 0; i < 4; i++){
        int currVal = pHand[i].first;
        int nextVal = pHand[i+1].first;
        if(nextVal-currVal != 1){
            ans = false;
            break;
        }
    }
    return ans;
}

bool isFlush(P pHand[5]){
    bool ans = true;
    for(int i = 0; i < 4; i++){
        string currSuit = pHand[i].second;
        string nextSuit = pHand[i+1].second;
        if(currSuit != nextSuit){
            ans = false;
            break;
        }
    }
    return ans;
}

int pairCount(P pHand[5]){
    int ans = 0;
    int counter[15] = {0};
    for(int i = 0; i < 5; i++){
        int curr = pHand[i].first;
        counter[curr]++;
    }
    for(int i = 0; i < 15; i++){
        if(counter[i] == 2) ans++;
    }
    return ans;
}

bool hasTwoPairs(P pHand[5]){
    bool ans = false;
    int pairCtr = 0;
    int counter[15] = {0};
    for(int i = 0; i < 5; i++){
        int curr = pHand[i].first;
        counter[curr]++;
    }
    for(int i = 0; i < 15; i++){
        if(counter[i] == 2) pairCtr++;
    }
    if(pairCtr == 2) ans = true;
    return ans;
}

bool hasTrio(P pHand[5]){
    bool ans = false;
    int counter[15] = {0};
    for(int i = 0; i < 5; i++){
        int curr = pHand[i].first;
        counter[curr]++;
    }
    for(int i = 0; i < 15; i++){
        if(counter[i] == 3) ans = true;
    }
    return ans;
}

bool isFullHouse(P pHand[5]){
    bool ans = false;
    bool trio = false;
    bool pair = false;
    int counter[15] = {0};
    for(int i = 0; i < 5; i++){
        int curr = pHand[i].first;
        counter[curr]++;
    }
    for(int i = 0; i < 15; i++){
        if(counter[i] == 3) trio = true;
        if(counter[i] == 2) pair = true;
    }
    if(trio && pair) ans = true;
    return ans;
}

bool isFourOfAKind(P pHand[5]){
    bool ans = false;
    int counter[15] = {0};
    for(int i = 0; i < 5; i++){
        int curr = pHand[i].first;
        counter[curr]++;
    }
    for(int i = 0; i < 15; i++){
        if(counter[i] == 4) ans = true;
    }
    return ans;
}


int findRank(P pHand[5]){
    int rank = 0;

    if(isStraight(pHand)){
        if(isFlush(pHand)){
            //check if straight or royal flush by checking highest card
            if(pHand[4].first == 14){
                //royal flush since Ace = 14
                rank = 10;
            }else rank = 9;
        }else rank = 5; //just a normal straight
    }else if(isFlush(pHand)){
        rank = 6;
    }else if(isFourOfAKind(pHand)){
        rank = 8;
    }else if(hasTrio(pHand)){
        //if hand has a trio, then it could be a Full House
        if(isFullHouse(pHand)){
            rank = 7;
        }else rank = 4;
    }else{
        //check pair counts
        int pCount = pairCount(pHand);
        if(pCount == 2) rank = 3; //2 Pairs
        else if(pCount == 1) rank = 2; //1 Pair
        else rank = 1; //No combinations - distinct cards
    }
    return rank;
}

//determine better hand based on highest card
int getHigherCard(P p1Hand[5], P p2Hand[5], int rank){
    int winner = 1;
    if(rank == 1){
        //high card hand
        for(int i = 4; i >= 0; i--){
            if(p1Hand[i].first > p2Hand[i].first) break;
            if(p2Hand[i].first > p1Hand[i].first){
                winner = 2;
                break;
            }
        }
    }else if(rank == 5 || rank == 6 || rank == 9){
        //straight, flush, straight flush
        if(p1Hand[4].first < p2Hand[4].first) winner = 2;
    }else if(rank == 8){
        //four of a kind
        int foak1 = 0, foak2 = 0; //4 of a kind card
        int solo1 = 0, solo2 = 0; //single card
        //get the 4oak and solo cards in hand
        if(p1Hand[0].first != p1Hand[1].first){
            solo1 = p1Hand[0].first;
            foak1 = p1Hand[1].first;
        }else{
            solo1 = p1Hand[4].first;
            foak1 = p1Hand[0].first; 
        }
        if(p2Hand[0].first != p2Hand[1].first){
            solo2 = p2Hand[0].first;
            foak2 = p2Hand[1].first;
        }else{
            solo2 = p2Hand[4].first;
            foak2 = p2Hand[0].first; 
        }
        //check if foak is the same or not
        if(foak1 < foak2) winner = 2;
        else if(foak1 == foak2){
            if(solo2 > solo1) winner = 2;
        }
    }else if(rank == 7){
        //three of a kind
        int trio1 = 0, trio2 = 0;
        int pair1 = 0, pair2 = 0;
        if(p1Hand[0].first != p1Hand[2].first){
            pair1 = p1Hand[0].first;
            trio1 = p1Hand[2].first;
        }else{
            pair1 = p1Hand[3].first;
            trio1 = p1Hand[0].first; 
        }
        if(p2Hand[0].first != p2Hand[2].first){
            pair2 = p2Hand[0].first;
            trio2 = p2Hand[2].first;
        }else{
            pair2 = p2Hand[3].first;
            trio2 = p2Hand[0].first; 
        }
        if(trio1 < trio2) winner = 2;
        else if(trio1 == trio2){
            if(pair2 > pair1) winner = 2;
        }
    }else{
        //pair, 2 pairs, 3 of a kind
        int vals1[15] = {0}, vals2[15] = {0};
        
        for(int i = 0; i < 5; i++){
            vals1[p1Hand[i].first]++;
            vals2[p2Hand[i].first]++;
        }

        if(rank == 2){
            //one pair
            int pair1 = 0, pair2 = 0;
            int high1 = 0, high2 = 0;
            for(int i = 0; i < 15; i++){
                if(vals1[i] == 2) pair1 = i;
                if(vals2[i] == 2) pair2 = i;
                if(vals1[i] == 1) high1 = max(high1,i);
                if(vals2[i] == 1) high2 = max(high2,i);
            }
            if(pair1 < pair2) winner = 2;
            else if(pair1 == pair2){
                if(high1 < high2) winner = 2;
            }
        }else if(rank == 3){
            //2 pairs
            int lowPair1 = 0, lowPair2 = 0, highPair1 = 0, highPair2 = 0;
            int high1 = 0, high2 = 0;
            for(int i = 0; i < 15; i++){
                if(vals1[i] == 2){
                    if(i > highPair1) {
                        lowPair1 = highPair1;
                        highPair1 = i;
                    }
                }
                if(vals2[i] == 2){
                    if(i > highPair2) {
                        lowPair2 = highPair2;
                        highPair2 = i;
                    }
                }
                if(vals1[i] == 1) high1 = max(high1,i);
                if(vals2[i] == 1) high2 = max(high2,i);
            }
            if(highPair1 < highPair2) winner = 2;
            else if(highPair1 == highPair2){
                if(lowPair1 < lowPair2) winner = 2;
                else if(lowPair1 == lowPair2){
                    if(high1 < high2) winner = 2;
                }
            }
        }else if(rank == 4){
            int trio1 = 0, trio2 = 0;
            for(int i = 0; i < 15; i++){
                if(vals1[i] == 3) trio1 = i;
                if(vals2[i] == 3) trio2 = i;
            }
            if(trio1 < trio2) winner = 2;
        }
    }
    return winner;
}

//solve method to determine winner
int solve(string hands) {
    int winner = 0;
    int handLen = hands.length();
 
    P p1Hand[5];
    P p2Hand[5];
    int ind = 0;

    //fix face cards and ace into numbers for simpler ordering and put pairs into separate player hand arrays
    for(int i = 0; i < handLen; i+=3) {
        string curr = hands.substr(i,2);
        string card = string(1,curr[0]), suit = string(1,curr[1]);

        if(curr[0] == 'T') card = "10";
        else if(curr[0] == 'J') card = "11";
        else if(curr[0] == 'Q') card = "12";
        else if(curr[0] == 'K') card = "13";
        else if(curr[0] == 'A') card = "14";

        P newHand = mp(stoi(card),suit);
        if(i < handLen/2) {
            p1Hand[ind++] = newHand;
            if(i+2 >= handLen/2) ind = 0;
        }
        else {
            p2Hand[ind++] = newHand;
        }
    }

    //sort by card values to help with determining kind of hand
    sort(p1Hand,p1Hand+5);
    sort(p2Hand,p2Hand+5);

    map<int,string> mapp;
    mapp[1] = "no combo";
    mapp[2] = "one pair";
    mapp[3] = "2 pair";
    mapp[4] = "trio";
    mapp[5] = "straight";
    mapp[6] = "flush";
    mapp[7] = "full house";
    mapp[8] = "four of a kind";
    mapp[9] = "straight flush";
    mapp[10] = "royal flush";
    

    //Find out rank of hand
    int p1Rank = findRank(p1Hand);
    int p2Rank = findRank(p2Hand);
    
    
    if(p1Rank > p2Rank) winner = 1;
    else if(p2Rank > p1Rank) winner = 2;
    else{
        //same hand so break the tie with highest card
        winner = getHigherCard(p1Hand,p2Hand,p1Rank);
    }
    
    return winner;
}



//==============================================================================

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int p1 = 0, p2 = 0;
    string line;
    while(getline(cin,line)){
        int winner = solve(line);
        if(winner == 1) p1++;
		else p2++;
    }
    cout << "Player 1: " << p1 << endl;
    cout << "Player 2: " << p2 << endl;
    return 0;
}


 