/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    static ListNode* addTwoNumbers(ListNode* node1, ListNode* node2) {
        ListNode *root = 0,*last = 0;
        bool bCarry = false;
        while(node1 || node2 || bCarry){
            int  iValue = 0;
            if(node1) {
                iValue += node1->val;
                node1 = node1->next;
            }
            
            if(node2){
                iValue += node2->val;
                node2 = node2->next;
            }
            
            if(bCarry){
                iValue += 1;
                bCarry = false;
            }
            
            if(iValue >= 10 ){
                bCarry = true;
                iValue -= 10;
            }
            
            if(!root) {//first insert
                root = last = new ListNode(iValue);
            } else  {
                last->next = new ListNode(iValue);
                last = last->next;
            }
        }
        return root;
    }
};

//=====================================
//test case
ListNode *generate_node(int value)
{
    ListNode *root = 0,*last = 0;
    while(value){
        if(root){
            last->next = new ListNode(value % 10);
            last = last->next;
        } else {
            root = last = new ListNode(value % 10);
        }
        value /= 10;
    }
    return root;
}

void print_node(ListNode *node)
{
    std::cout<<"[";
    while(node){
        std::cout<<node->val;
        node = node->next;
        if(node){
            std::cout<<",";
        }
    }
    std::cout<<"]"<<"\n";
}


int main()
{
    ListNode *node1 = generate_node(123);//[3,2,1]
    ListNode *node2 = generate_node(876);//[6,7,8]
    print_node(Solution::addTwoNumbers(node1,node2));
    return 0;
}
