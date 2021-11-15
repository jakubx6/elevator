#include "elevator.h"

//Constructor
Elevator::Elevator(char i) : id(i), cur(0), tar(0), dir(0) {
    q = new queue;
};

void Elevator::status(Elevator* m, int n) {
    for (int i = 0; i < n; i++) {
        cout << m[i].id << " " << m[i].cur << " " << m[i].tar << " " << m[i].dir << endl;
    }

}

void Elevator::step(Elevator* m, int n) {
    for (int i = 0; i < n; i++) {
        //step current to tagret
        if (m[i].tar != m[i].cur) {
            if (m[i].dir > 0) {
                m[i].cur++;
            }
            else if (m[i].dir < 0) {
                m[i].cur--;
            }
            else if (m[i].dir == 0) {
                if (m[i].cur > 0) {
                    m[i].cur--;
                }
                else {
                    m[i].cur++;
                }

            }
        }
        //get next target, direction up
        else if (m[i].tar == m[i].cur && m[i].dir == 1 && m[i].que.size() > 0) {
            m[i].tar = *m[i].que.begin();
            m[i].que.erase(*m[i].que.begin());
            continue;
        }
        //get next target, direction down
        else if (m[i].tar == m[i].cur && m[i].dir == -1 && m[i].qdw.size() > 0) {
            m[i].tar = *m[i].qdw.begin();
            m[i].qdw.erase(*m[i].qdw.begin());
            continue;
        }//get next target, direction up to down
        else if (m[i].tar == m[i].cur && m[i].dir == 1 && m[i].qdw.size() > 0) {
            m[i].dir = -1;
            m[i].tar = *m[i].qdw.begin();
            m[i].qdw.erase(*m[i].qdw.begin());
            continue;
        }//get next target, direction down to up
        else if (m[i].tar == m[i].cur && m[i].dir == -1 && m[i].que.size() > 0) {
            m[i].dir = 1;
            m[i].tar = *m[i].que.begin();
            m[i].que.erase(*m[i].que.begin());
            continue;
        }
        //get to 0
        else if (m[i].cur != 0) {
            m[i].tar = 0;
            m[i].dir = 0;
            continue;
        }
        else if (m[i].cur == 0) {
            m[i].dir = 0;
            continue;
        }
        else {
            error(1);
        }
    }
}

void Elevator::pickup(Elevator* m, int n, int c, int t) {
    int d = 1;
    if (c > t) {
        d = -1;
    }
    else if (c == t) {
        error(2);
        return;
    }
    //pick minecart from 0
    for (int i = 0; i < n; i++) {
        if (m[i].dir == 0) {
            if (d > 0) {
                m[i].tar = c;
                m[i].que.insert(t);
                m[i].dir = 1;
            }
            else {
                m[i].tar = c;
                m[i].qdw.insert(t);
                if (m[i].dir == 0) {
                    m[i].dir = 1;
                }
                else {
                    m[i].dir = -1;
                }

            }
            return;
        }
    }
    //pick minecart on the road
    for (int i = 0; i < n; i++) {
        if (m[i].dir == 1 && d == 1 && m[i].cur <= c) {
            m[i].que.insert(c);
            m[i].que.insert(t);
            m[i].que.insert(m[i].tar);
            m[i].tar = *m[i].que.begin();
            m[i].que.erase(*m[i].que.begin());
            return;
        }
        else if (m[i].dir == -1 && d == -1 && m[i].cur >= c) {
            m[i].qdw.insert(c);
            m[i].qdw.insert(t);
            m[i].qdw.insert(m[i].tar);
            m[i].tar = *m[i].qdw.begin();
            m[i].qdw.erase(*m[i].qdw.begin());
            return;
        }
    }
    //pick minecart near
    for (int i = 0, min, min_i; i < n; i++) {
        if (d < 0) {
            if (i == 0) {
                min = abs(*m[i].que.rbegin() - c) + m[i].que.size();
                min_i = i;
                continue;
            }
            if (min > abs(*m[i].que.rbegin() - c) + m[i].que.size()) {
                min = abs(*m[i].que.rbegin() - c) + m[i].que.size();
                min_i = i;
            }
            if (i == n - 1) {
                m[min_i].qdw.insert(c);
                m[min_i].qdw.insert(t);
                return;
            }
        }
        else if (d > 0) {
            if (i == 0) {
                min = abs(*m[i].qdw.rbegin() - c) + m[i].qdw.size();
                min_i = i;
                continue;
            }
            if (min > abs(*m[i].qdw.rbegin() - c) + m[i].qdw.size()) {
                min = abs(*m[i].qdw.rbegin() - c) + m[i].qdw.size();
                min_i = i;
            }
            if (i == n - 1) {
                m[min_i].que.insert(c);
                m[min_i].que.insert(t);
                return;
            }
        }
    }
    error(4);
}

void Elevator::update(Elevator* m, int n, char id, int t, int d) {
    for (int i = 0; i < n; i++) {
        if (m[i].id == id) {
            m[i].tar = t;
            m[i].dir = d;
            return;
        }
    }
    error(5);
}

void Elevator::request(Elevator* m, int n, char id, int t) {
    int d = 1;
    for (int i = 0; i < n; i++) {
        if (m[i].id == id) {
            if (m[i].cur > t) {
                d = -1;
            }
            if (m[i].dir == 0) {
                m[i].dir = d;
                m[i].tar = t;
            }
            else if (d == 1) {
                m[i].que.insert(t);
            }
            else if (d == -1) {
                m[i].qdw.insert(t);
            }
            return;
        }
    }
    error(6);
}

void Elevator::error(int err)
{
    cout << "error " << err << endl;
    system("pause");
}