#include<bits/stdc++.h>
using namespace std;
struct Node {//define the structure of the node
    string value;
    Node* left;
    Node* right;
    Node(string val, Node* l = nullptr, Node* r = nullptr) : value(val), left(l), right(r) {}
};
bool isoperator(string &c)//check if the string is an operator
{
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "^"|| c == "ln";
}
int Precendence(string &op)
{
    if (op == "+" || op == "-")return 1;
    if (op == "*" || op == "/")return 2;//* and / have higher precedence than + and -
    if (op == "^")return 3;//^ is the power operator,with the higher precedence
    if (op == "ln")return 4;//ln is the natural logarithm operator,with the highest precedence
    return 0;
}
bool isVariable(string &s) // Check if a string is a variable
{
    for (char c : s) {
        if (!isalpha(c)) return false;
    }
    return true;
}
vector<string> Tokenize(string s)//divide the string into tokens
{
    vector<string> tokens;
    string token;
    for(char c : s)
    {
        string tmp = string(1,c);//convert the character into string
        if (c == ' ')continue;
        else if (c == '(' || c == ')')//if the character is a bracket,then push it into tokens
        {
            if (!token.empty())
            {
                tokens.push_back(token);//push the token into tokens
                token.clear();
            }
            tokens.push_back(string(1, c));
        }
        else if (isoperator(tmp))//
        //if the character is an operator,then push it into tokens
        {
            if (!token.empty())
            {
                tokens.push_back(token);//push the token into tokens
                token.clear();
            }
            tokens.push_back(string(1, c));//push the operator into tokens
        }
        else
        {
            token += c;//if the character is not an operator,then add it to the token,in case that the character is not a single character
        }
    }
    if (!token.empty())//if the token is not empty,then push it into tokens
    {
        tokens.push_back(token);
    }
    return tokens;
}
Node* copySubtree(Node* node) {//copy the subtree of the node
    if (!node) return nullptr;
    Node* newNode = new Node(node->value);//create a new node with the value of the node
    newNode->left = copySubtree(node->left);//copy the left subtree of the node
    newNode->right = copySubtree(node->right);//copy the right subtree of the node
    return newNode;
}
vector<string> infixtopostfix(vector<string> &tokens)
{
    //if the stack is empty or the precedence of the top operator is less than the precedence of the current operator
    //then push the current operator into the stack
    stack<string> s;//use a stack to store the operators
    vector<string> postfix;//use a vector to store the postfix expression
    for (string token : tokens)
    {
        if (isdigit(token[0]) || isalpha(token[0]))//if the token is a number or a variable
        {
            postfix.push_back(token);
        }
        else if (token == "(")
        {
            s.push(token);//push the bracket into the stack
        }
        else if (token == ")")
        {
            while (!s.empty() && s.top() != "(")
            {
                postfix.push_back(s.top());//push the top of the stack into the postfix
                s.pop();
            }
            s.pop();
        }
        else
        {
            while (!s.empty() && Precendence(s.top()) >= Precendence(token))
            //if the precedence of the top of the stack is higher than the initial token
            //then push the top into the postfix and pop
            {
                postfix.push_back(s.top());//push the top of the stack into the postfix
                s.pop();
            }
            s.push(token);
        }
    }
    while (!s.empty())
    {
        postfix.push_back(s.top());//push the top of the stack into the postfix
        s.pop();
    }
    return postfix;
}
Node* buildtree(vector<string> &postfix)//build binary tree with postfix
{
    stack<Node*> st;//st is used to push the node in
    for(string& s : postfix)
    {
        if(isoperator(s))//if s is an operator,then build a new node with the value of s
        //and its left and right child are the top two node of st
        {
            Node* node = new Node(s,NULL,NULL);
            node->right = st.top();
            st.pop();
            node->left = st.top();
            st.pop();
            st.push(node);//push the operator back into the stack
        }
        else st.push(new Node(s,NULL,NULL));//push the new variale into the stack
    }
    return st.top();//return the root of the tree
}


Node* Diff(Node* node, string& s) {//calculate the derivative of the expression
    if (!node) return new Node("0");
    if (node->value == s) return new Node("1");

    Node* Leftdiff = Diff(node->left, s);//recursively calculate the derivative of the left child
    Node* Rightdiff = Diff(node->right, s);//recursively calculate the derivative of the right child

    if (node->value == "+") {
        return new Node("+", Leftdiff, Rightdiff);
    } else if (node->value == "-") {
        return new Node("-", Leftdiff, Rightdiff);
    } else if (node->value == "*") {//use the product rule to calculate the derivative of the product of two functions
        if (node->left->value == s) {
            return copySubtree(node->right);
        }
        else if (node->right->value == s) 
            return copySubtree(node->left); 
        else {
            // General case for product rule
            return new Node("+", new Node("*", Leftdiff, new Node(node->right->value)), new Node("*", new Node(node->left->value), Rightdiff));
        }
    } else if (node->value == "/") {//use the quotient rule to calculate the derivative of the quotient of two functions
        // (f'g - fg') / g^2
        Node* numerator = new Node("-", new Node("*", Leftdiff, new Node(node->right->value)), new Node("*", new Node(node->left->value), Rightdiff));
        Node* denominator = new Node("^", new Node(node->right->value), new Node("2"));
        return new Node("/", numerator, denominator);
    } else if (node->value == "^") {//use the chain rule to calculate the derivative of the power of two functions
        if (node->right->value == s) {
            // a^b * ln(a)
            Node* baseLog = new Node("ln", new Node(node->left->value), nullptr);
            return new Node("*", new Node("^", new Node(node->left->value), new Node(node->right->value)), baseLog);
        } 
        else if (node->left->value == s) {//if the left child is the variable,then calculate the derivative of the power of two functions
            // b * a^(b-1)
            Node* newExponent = new Node("-", new Node(node->right->value), new Node("1"));
            return new Node("*", new Node(node->right->value), new Node("^", new Node(node->left->value), newExponent));
        }
    }
    return new Node("0");
}

string expressionToString(Node* node) {
    if (!node) return "";
    //if(isoperator(node->value)) return "";
    if (!node->left && !node->right) return node->value; // Leaf node
    string leftExpr = expressionToString(node->left);
    string rightExpr = expressionToString(node->right);
    if (node->value == "ln") {//if the operator is ln,then add brackets to the left expression
        return "ln(" + leftExpr + ")";
    }
    if(leftExpr.empty() && rightExpr.empty()) return ""; // Both children are nullptr (should not happen)
    if(leftExpr.empty()) return rightExpr;//if the left expression is empty,then return the right expression
    if(rightExpr.empty()) return leftExpr;//if the right expression is empty,then return the left expression
    if (node->value == "+" || node->value == "-") {//if the operator is + or -,then add brackets to the left and right expression
        return leftExpr + "" + node->value + "" + rightExpr;
    } else if (node->value == "*") {
        if (node->left && (node->left->value == "+" || node->left->value == "-")) leftExpr = "(" + leftExpr + ")";
        if (node->right && (node->right->value == "+" || node->right->value == "-")) rightExpr = "(" + rightExpr + ")";
        return leftExpr + "" + node->value + "" + rightExpr;
    } else if (node->value == "/") {//if the operator is /,then add brackets to the left and right expression
        if (node->left && (node->left->value == "+" || node->left->value == "-")) leftExpr = "(" + leftExpr + ")";
        return leftExpr + "" + node->value + "" + rightExpr;
    }else if (node->value == "^") {
        // Enclose base in parentheses if it's an expression
        if (node->left && (node->left->value == "+" || node->left->value == "-" || node->left->value == "*" || node->left->value == "/")) leftExpr = "(" + leftExpr + ")";
        // Enclose exponent in parentheses if it's an expression
        if (node->right && (node->right->value == "+" || node->right->value == "-" || node->right->value == "*" || node->right->value == "/")) rightExpr = "(" + rightExpr + ")";
        return leftExpr + " ^ " + rightExpr; 
    }
    return "0"; // For unsupported operations or values
}

int main()
{
    string s;
    cin>>s;
    vector<string> tokens = Tokenize(s);//divide the string into tokens
    vector<string> postfix = infixtopostfix(tokens);//convert the infix expression into postfix
    Node* exprTree = buildtree(postfix);//build the binary tree with the postfix expression
    unordered_set<string> printedTokens;//use a set to store the printed tokens,incase of the repeated tokens

    for (string& token : tokens) 
    {
        if (isVariable(token) && printedTokens.find(token) == printedTokens.end()) {//if the token is a variable and it is not printed
            Node* derivativeTree = Diff(exprTree, token);//calculate the derivative of the expression
            string derivativeExpr = expressionToString(derivativeTree);//convert the tree into string
            cout << token << " : " << derivativeExpr << endl;
            printedTokens.insert(token);//insert the token into the set
            delete derivativeTree; 
        }
    }
    return 0;
}