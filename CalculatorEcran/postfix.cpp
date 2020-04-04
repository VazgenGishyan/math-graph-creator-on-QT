#include "postfix.h"


Postfix::Postfix()
{
    clear();
}

void Postfix::clear()
{
    postfix.clear();
    //isConstExpression = true;
    postfixCreated = false;
}

void Postfix::createPostfix(const Expression & expression)
{
    if(!expression.ended())
    {
        throw Error("Expression not ended");
        //qDebug()<<"! ended";
        //throw 1;
    }
    list<ExpressionElement>::const_iterator it = expression.it_begin();
    list<ExpressionElement>::const_iterator itend = expression.it_end();
    createPostfix(it,itend);
    postfixCreated = true;
}

void Postfix::createPostfix(list<ExpressionElement>::const_iterator & it, list<ExpressionElement>::const_iterator & itend)
{
    stack<ExpressionElement> st;
    bool minus = true;
    ExpressionElementType lasttype = nothing;
    ExpressionElementType presenttype;
    for (; it != itend; ++it)
    {
        presenttype = it->getType();
        switch (presenttype)
        {
        case var:
            //isConstExpression = false;
        case num:
        case constant:
        case factorial:
            //cout << (*it).getName() << endl;
            postfix.push_back(*it);
            break;
        case func:
            {
                ExpressionElement temp = *it;
                createPostfix(++it,itend);
                postfix.push_back(temp);
            }
            break;
        case begin:
            createPostfix(++it, itend);
            break;
        case oper:
        case sub:
            switch (lasttype)
            {
            case nothing:
                if (presenttype == sub && minus)
                {
                    ExpressionElement temp(Numbers::num0, ExpressionElementType::num);
                    //cout << (temp).getName() << endl;
                    postfix.push_back(temp);
                }
                st.push(*it);
                break;
            default:
                int operatorlevel = getOperatorLevel((*it).getName());
                while (!st.empty() && operatorlevel <= getOperatorLevel(st.top().getName()))
                {
                    //cout << (st.top()).getName() << endl;
                    postfix.push_back(st.top());
                    st.pop();
                }
                st.push(*it);
                break;
            }
            lasttype = presenttype;
            break;
        case end:
            while (!st.empty())
            {
                //cout << (st.top()).getName() << endl;
                postfix.push_back(st.top());
                st.pop();
            }
            return;
            //break;
        default:
            throw FatalError("Wrong element in expression");
        }
        minus = false;
    }
    while (!st.empty())
    {
        //cout << (st.top()).getName() << endl;
        postfix.push_back(st.top());
        st.pop();
    }
}

bool Postfix::created() const
{
    return postfixCreated;
}

list<ExpressionElement>::const_iterator Postfix::it_end() const
{
    list<ExpressionElement>::const_iterator ret = postfix.end();
    return ret;
}

list<ExpressionElement>::const_iterator Postfix::it_begin() const
{
    list<ExpressionElement>::const_iterator ret = postfix.begin();
    return ret;
}
