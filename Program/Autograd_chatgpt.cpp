#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

// 定义表达式树的节点结构
struct Node {
    string value; // 节点的值，可以是操作符或变量/常量
    Node* left;   // 左子节点
    Node* right;  // 右子节点
    
    Node(string val,Node* left,Node* right) : value(val), left(nullptr), right(nullptr) {}
};

// 判断一个字符串是否是操作符
bool isOperator(const string& c) {
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "^";
}

// 判断一个字符串是否是变量（这里简化为判断是否全部由字母组成）
bool isVariable(const string& s) {
    for (char c : s) {
        if (!isalpha(c)) return false;
    }
    return true;
}

// 获取操作符的优先级
int getPrecedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

// 将中缀表达式转换为后缀表达式（逆波兰表示法）
vector<string> infixToPostfix(const vector<string>& tokens) {
    stack<string> s;
    vector<string> postfix;
    for (const string& token : tokens) {
        if (isVariable(token) || isdigit(token[0])) {
            postfix.push_back(token);
        } else if (token == "(") {
            s.push(token);
        } else if (token == ")") {
            while (!s.empty() && s.top() != "(") {
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop(); // Pop "("
        } else {
            while (!s.empty() && getPrecedence(s.top()) >= getPrecedence(token)) {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(token);
        }
    }
    while (!s.empty()) {
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}

// 根据后缀表达式构建表达式树
Node* constructTree(const vector<string>& postfix) {
    stack<Node*> st;
    for (const string& token : postfix) {
        if (isOperator(token)) {
            Node* node = new Node(token);
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
            st.push(node);
        } else {
            st.push(new Node(token));
        }
    }
    return st.top();
}

// 对表达式树进行微分
Node* differentiate(const Node* node, const string& var) {
    if (node == nullptr) return nullptr;

    if (node->value == var) {
        return new Node("1"); // 变量对自身的导数为1
    } else if (!isOperator(node->value)) {
        return new Node("0"); // 常量的导数为0
    }

    Node* diffLeft = differentiate(node->left, var); // 递归对左子树求导
    Node* diffRight = differentiate(node->right, var); // 递归对右子树求导

    // 根据不同的操作符应用相应的微分规则
    if (node->value == "+") {
        return new Node("+",diffLeft, diffRight);
    } else if (node->value == "-") {
        return new Node("-", diffLeft, diffRight);
    } else if (node->value == "*") {
        return new Node("+", new Node("*", diffLeft, new Node(node->right->value)), new Node("*", new Node(node->left->value), diffRight));
    } else if (node->value == "/") {
        Node* numerator = new Node("-", new Node("*", diffLeft, new Node(node->right->value)), new Node("*", new Node(node->left->value), diffRight));
        Node* denominator = new Node("^", new Node(node->right->value), new Node("2"));
        return new Node("/", numerator, denominator);
    } else if (node->value == "^") {
        // 处理指数函数的微分
        if (isVariable(node->left->value) && !isVariable(node->right->value)) {
            if (node->right->value == "1") {
                return new Node("*", new Node(node->right->value), diffLeft);
            } else {
                return new Node("*", new Node("*", new Node(node->right->value), new Node("^", new Node(node->left->value), new Node(to_string(stoi(node->right->value) - 1)))), diffLeft);
            }
        } else if (!isVariable(node->left->value) && isVariable(node->right->value)) {
            return new Node("*", new Node("*", new Node(node->right->value), new Node("^", node->left, new Node(to_string(stoi(node->right->value) - 1)))), diffLeft);
        }
    }

    // 未处理的情况
    return new Node("0");
}

// 将表达式树转换为字符串形式
string expressionToString(const Node* node) {
    if (!node) return "";
    if (!node->left && !node->right) return node->value;
    string leftExpr = expressionToString(node->left);
    string rightExpr = expressionToString(node->right);
    if (node->value == "+" || node->value == "-") {
        return "(" + leftExpr + " " + node->value + " " + rightExpr + ")";
    } else if (node->value == "*" || node->value == "/") {
        return leftExpr + " " + node->value + " " + rightExpr;
    } else if (node->value == "^") {
        return leftExpr + "^" + rightExpr;
    }
    return "";
}

// 将输入的表达式分割为符号列表
vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string token;
    for (char ch : expr) {
        if (isspace(ch)) continue;
        if (isOperator(string(1, ch)) || ch == '(' || ch == ')') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, ch));
        } else {
            token += ch;
        }
    }
    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

int main() {
    string expr;
    cout << "请输入一个代数表达式: ";
    getline(cin, expr);

    vector<string> tokens = tokenize(expr);
    vector<string> postfix = infixToPostfix(tokens);
    Node* exprTree = constructTree(postfix);

    for (const string& token : tokens) {
        if (isVariable(token)) {
            Node* derivativeTree = differentiate(exprTree, token);
            string derivativeExpr = expressionToString(derivativeTree);
            cout << "表达式 " << expr << " 对 " << token << " 的导数为: " << derivativeExpr << endl;
            delete derivativeTree; // 删除导数树以避免内存泄露
        }
    }

    delete exprTree; // 删除表达式树以避免内存泄露
    return 0;
}
