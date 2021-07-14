#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>

class Node {
    public: char c_Alpha;
    public: int i_Freq;
    public: Node* op_LCh;
    public: Node* op_RCh;

    public: Node(char c_Alpha, int i_Freq, Node* op_LCh,
                 Node* op_RCh) {
        this->c_Alpha = c_Alpha;
        this->i_Freq = i_Freq;
        this->op_LCh = op_LCh;
        this->op_RCh = op_RCh;
    }
};

class Huffman{
    public: std::unordered_map<char, int> o_FMap;
    public: std::deque<Node*> o_Fore;
        public: Huffman(){
        char c_Char;
        while((c_Char = getchar()) != EOF) {
            if(c_Char == '\n'){
                continue;
            }
            if(o_FMap.count(c_Char)){
                o_FMap[c_Char]++;
            }
            else{
                 o_FMap[c_Char] = 1;
            }
        }
        fn_BuildTree();
    }

    public: ~Huffman(){
        for(auto ip_Item = o_Fore.begin();
            ip_Item != o_Fore.end();
            ip_Item++){
            delete *ip_Item;
        }
    }

    public: void fn_ShowCode(Node* op_Ptr, std::string s_Str) {
                if(op_Ptr->op_LCh == nullptr ||
                   op_Ptr->op_RCh == nullptr) {
                    std::cout<< op_Ptr->c_Alpha << " (i_Freq = "
                             << o_FMap[op_Ptr->c_Alpha]<<
                                ") --> "<<s_Str<<"\n";
                    return;
                }
                if(op_Ptr->op_LCh){
                        fn_ShowCode(op_Ptr->op_LCh, (s_Str + "0"));
                }
                if(op_Ptr->op_RCh){
                    fn_ShowCode(op_Ptr->op_RCh, (s_Str + "1"));
                }
            }

    public: struct NodeCom{
                public: bool operator() (Node* op_Fir, Node* op_Sec) {
                    bool b_IsLess = false;
                    if(op_Fir->i_Freq < op_Sec->i_Freq){
                        b_IsLess = true;
                    }
                    return b_IsLess;
                }
            } o_Com;
    private: void fn_BuildTree(){
        for(std::unordered_map<char, int>::iterator op_Item = o_FMap.begin();
            op_Item != o_FMap.end(); op_Item++){
            o_Fore.push_back(new Node(
                                      op_Item->first,
                                      op_Item->second,
                                      nullptr,
                                      nullptr)
                             );
        }

        for(int i_Ct = 0; i_Ct < o_FMap.size()-1; i_Ct++) {
            std::sort(o_Fore.begin(), o_Fore.end(), o_Com);
            Node* op_Tmp1 = o_Fore.front();
            o_Fore.pop_front();
            Node* op_Tmp2 = o_Fore.front();
            o_Fore.pop_front();
            Node* op_NewNode = new Node('\0',
                                        op_Tmp1->i_Freq + op_Tmp2->i_Freq,
                                        op_Tmp1,
                                        op_Tmp2);
            o_Fore.push_back(op_NewNode);
        }
    }
};



int main() {
    Huffman o_Huff;

    o_Huff.fn_ShowCode(o_Huff.o_Fore.front(), "");
    return 0;
}
