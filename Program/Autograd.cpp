#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;
    Node(string val) : value(val), left(nullptr), right(nullptr) {}
    ~Node() {
        delete left;
        delete right;
    }
};

bool isOperator(const string& c) {
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "^";
}

bool isVariable(const string& s) {
    // 假设变量是由字母组成的字符串
    for (char c : s) {
        if (!isalpha(c)) return false;
    }
    return true;
}

int getPrecedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

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

Node* differentiate(const Node* node, const string& var) {
    if (node == nullptr) return nullptr;

    if (node->value == var) {
        return new Node("1");
    } else if (!isOperator(node->value)) {
        return new Node("0");
    }

    Node* diffLeft = differentiate(node->left, var);
    Node* diffRight = differentiate(node->right, var);

    if (node->value == "+") {
        return new Node("+", diffLeft, diffRight);
    } else if (node->value == "-") {
        return new Node("-", diffLeft, diffRight);
    } else if (node->value == "*") {
        return new Node("+", new Node("*", diffLeft, new Node(node->right->value)), new Node("*", new Node(node->left->value), diffRight));
    } else if (node->value == "/") {
        Node* numerator = new Node("-", new Node("*", diffLeft, new Node(node->right->value)), new Node("*", new Node(node->left->value), diffRight));
        Node* denominator = new Node("^", new Node(node->right->value), new Node("2"));
        return new Node("/", numerator, denominator);
    } else if (node->value == "^") {
        // This is a simplified version for differentiation of power functions where the exponent is a constant.
        // A more general implementation should handle cases where the exponent is not a constant.
        if (isVariable(node->left->value) && !isVariable(node->right->value)) {
            return new Node("*", new Node("*", new Node(node->right->value), new Node("^", new Node(node->left->value), new Node(to_string(stoi(node->right->value) - 1)))), diffLeft);
        }
    }

    // Placeholder for unhandled cases
    return new Node("0");
}

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
    cout << "Enter an algebraic expression: ";
    getline(cin, expr);

    vector<string> tokens = tokenize(expr);
    vector<string> postfix = infixToPostfix(tokens);
    Node* exprTree = constructTree(postfix);

    for (const string& token : tokens) {
        if (isVariable(token)) {
            Node* derivativeTree = differentiate(exprTree, token);
            string derivativeExpr = expressionToString(derivativeTree);
            cout << "The derivative of " << expr << " with respect to " << token << " is: " << derivativeExpr << endl;
            delete derivativeTree;
        }
    }

    delete exprTree;
    return 0;
}