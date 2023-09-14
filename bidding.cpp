#include <iostream>

using namespace std;

class Bidding{
public:
    string name;
    int money;
    Bidding(string _name = "", int _money = 0){
        name = _name;
        money = _money;
    }
};

void sortBidders(Bidding *bidders, int count){
    for(int i = 0; i < count; i++){
        for(int j = 0; j < count - i - 1; j++){
            if(bidders[j].money < bidders[j + 1].money){
                Bidding temp = bidders[j];
                bidders[j] = bidders[j + 1];
                bidders[j + 1] = temp;
            }
        }
    }
}

int main(){
    int count;
    string name;
    int money;

    cin >> count;
    Bidding *bidders = new Bidding[count];

    for(int i = 0; i < count; i++){
        cin >> name >> money;
        bidders[i] = Bidding(name, money);
    }

    sortBidders(bidders, count);

    int highestBidderIndex = 0;

    for(int i = 0; i < count-1; i++){
        while(bidders[highestBidderIndex].money == bidders[highestBidderIndex+1].money){
            if(bidders[i].money == bidders[i+1].money){
                i++;
            }
            else{
                i++;
                break;
            }
        }
        highestBidderIndex = i;
        if(bidders[i].money == bidders[count-1].money){
            highestBidderIndex = -1;
            break;
        }
        if(bidders[i].money != bidders[i+1].money){
            break;
        }
    }

    if(highestBidderIndex == -1){
        cout << "NONE";
    }
    else{
        cout << bidders[highestBidderIndex].name;
    }

    return 0;
}