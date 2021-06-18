#include<bits/stdc++.h>
#define pb push_back
#define loop(i,a,b) for (auto i = a; i < b; i++)
#define itrloop(itr,x) for(auto itr=x.begin();itr!=x.end();itr++)
#define Sz(x) (int)x.size()
#define nl cout<<endl

using namespace std;
typedef long long ll;
typedef vector<string> vs;

//global variables
ll totalBlockWeight=4000000;      //Upper limit of the weight given in question
set<string> included_trx_ids;     //stores transaction ID which are included or counted

//Make a class to objectify each transaction.
class TransactionInfo {
public:
    ll fee;
    ll weight;
    string trans_id;
    vs parent_id;
};

//Read the CSV file from the source directory and update it in an unordered_map in 0(1) time.
void readCSV(string filename,unordered_map<string, TransactionInfo * > & trx){
    ifstream fin(filename);
    vs trxDetails;
    string line,word;
    getline(fin,line);
    while(getline(fin,line)){     //get input from the file line by line in loop
        trxDetails.clear();
        stringstream s(line);       // About stringstream: A stringstream associates a string object with a stream allowing you to read from the string as if it were a stream.
        while(getline(s,word,',')){     //get each words from the stringstream using the separator as ',' which is found in CSV file.
            trxDetails.pb(word);        //push each word in the details section for each transaction(row-wise)
        }
        auto trxInfo = new TransactionInfo();     //create transaction object amd update it with data from the CSV
        trxInfo->trans_id=trxDetails[0];
        trxInfo->fee=stoi(trxDetails[1]);
        trxInfo->weight=stoi(trxDetails[2]);
        vs parent_id;
        loop(i,3,Sz(trxDetails)){
            parent_id.pb(trxDetails[i]);
        }
        trxInfo->parent_id=parent_id;
        trx[trxInfo->trans_id]=trxInfo;      //push each transaction in the map with transactionID as key
    }
    fin.close();
    cout<<"Total Transaction Read: "<<Sz(trx);nl;
}
/*
    Current validation is done by skipping transactions having uncompleted parent transaction.
    Further validation update can be made here.
*/
bool ValidateTransaction(TransactionInfo* trx,set<string>& included_trx_ids){
    for(auto parent_id:trx->parent_id)
        if(included_trx_ids.find(parent_id)==included_trx_ids.end()) 
            return false;
    return true;
}

int main(){
    ll currentBlockWeight=0,totalFee=0;
    unordered_map<string,TransactionInfo * > trx;    //initialize emtpy map fo be filled when data is read from the CSV.
    readCSV("mempool.csv",trx); 
    set<pair<float,TransactionInfo * >,greater<pair<float,TransactionInfo * >>> transactionSet;  //  to maintain the descending order of fee/weight for each transaction.
    set<string> transaction_set_included;    //transaction to be added to block goes in this.
    vs output;        //maintain the order of the output.
    for(auto x:trx){
        transactionSet.insert({(float)x.second->fee/x.second->weight,x.second});
    }
    //till here transactions are arranged in descending order by their fee/weight ratio
    while(!transactionSet.empty() && currentBlockWeight<totalBlockWeight){
        int found =0;
        itrloop(itr,transactionSet){
            TransactionInfo* currentTransaction = (*itr).second;
            ll curFee = currentTransaction->fee;
            ll curWeight=currentTransaction->weight;
            if(ValidateTransaction(currentTransaction,included_trx_ids) && currentBlockWeight+curWeight<=totalBlockWeight){   //use the validate function and make sure the total_block_weight has been reached or not.
                currentBlockWeight+=curWeight;
                transaction_set_included.insert(currentTransaction->trans_id);
                output.pb(currentTransaction->trans_id);
                totalFee+=curFee;
                transactionSet.erase(itr);
                found =1;
                break;
            }
        }
        if(found==0) break;
    }
    cout << "No. of transaction in final block: " << transaction_set_included.size() << endl;
    cout << "Total fee till current block: " << totalFee << endl;
    cout << "Total weight till current block: " << currentBlockWeight << endl;
    ofstream myfile("block.txt");
    for(auto s: output) myfile<<s<<endl;
    myfile.close();
}