// 题目：353. 设计贪吃蛇（Design Snake Game）
// 思路：双端队列按“队首蛇头、队尾蛇尾”存蛇身坐标编码，哈希集合记录占用格子；每步先算新头，再判越界、判吃食物，最后判自撞并入队。
// 时间复杂度：move 为 O(1)；空间复杂度：O(width × height)，蛇身与占用集合的最大规模。
class SnakeGame {  // 贪吃蛇游戏的数据结构类
public:  // 对外接口
    SnakeGame(int width, int height, vector<vector<int>>& food) {  // width 为列数，height 为行数，food 是按出现顺序给出的食物坐标
        m = height;  // 记录行数，即 x 方向的取值范围
        n = width;  // 记录列数，即 y 方向的取值范围
        this->food = food;  // 保存食物序列，后面用 idx 顺序取用
        score = 0;  // 初始得分为 0
        idx = 0;  // 下一个待吃食物的下标
        q.push_back(0);  // 蛇身用双端队列存坐标编码，初始只有 (0,0)，编码为 0
        vis.insert(0);  // 同时把 (0,0) 放入占用集合，便于 O(1) 判重
    }  // 构造函数结束

    int move(string direction) {  // 按方向走一步并返回得分；撞墙或撞到自己返回 -1
        int p = q.front();  // 队首就是蛇头
        int i = p / n, j = p % n;  // 用行优先编码还原蛇头的 row、col
        int x = i, y = j;  // x、y 为移动后的新蛇头坐标，先复制当前蛇头
        if (direction == "U") {  // 向上：行号减一
            --x;  // 上移一行
        } else if (direction == "D") {  // 向下：行号加一
            ++x;  // 下移一行
        } else if (direction == "L") {  // 向左：列号减一
            --y;  // 左移一列
        } else {  // 剩下只可能是向右
            ++y;  // 右移一列
        }  // 方向处理结束
        if (x < 0 || x >= m || y < 0 || y >= n) {  // 越界即撞墙，游戏结束
            return -1;  // 返回 -1 表示游戏结束
        }  // 撞墙判断结束
        if (idx < food.size() && x == food[idx][0] && y == food[idx][1]) {  // 新蛇头正好是下一个待吃的食物
            ++score;  // 吃到食物，得分加一
            ++idx;  // 该食物已消费，指向下一个
        } else {  // 没吃到食物，蛇身长度保持不变
            int tail = q.back();  // 取出蛇尾的坐标编码
            q.pop_back();  // 蛇尾离开，长度不变
            vis.erase(tail);  // 蛇尾格子不再被占用，从集合中删除
        }  // 是否吃到食物的分支结束
        int cur = f(x, y);  // 把新蛇头坐标编码成一维编号
        if (vis.count(cur)) {  // 新蛇头撞到仍在场上的身体就直接结束
            return -1;  // 返回 -1 表示游戏结束
        }  // 自撞判断结束
        q.push_front(cur);  // 新蛇头从队首入队
        vis.insert(cur);  // 标记该格子已被身体占用
        return score;  // 返回当前得分
    }  // move 结束

private:  // 以下为内部状态
    int m;  // 行数
    int n;  // 列数
    vector<vector<int>> food;  // 食物序列
    int score;  // 当前得分，等于已吃食物数
    int idx;  // 下一个待吃食物的下标
    deque<int> q;  // 蛇身：队首为蛇头，队尾为蛇尾
    unordered_set<int> vis;  // 蛇身占用格子的集合，用于 O(1) 判重

    int f(int i, int j) {  // 把二维坐标压成一维编号，便于放进集合
        return i * n + j;  // 行优先编码：行号乘列数再加列号
    }  // f 结束
};  // 类定义结束

// 下面是 LeetCode 模板注释，仅演示对象的构造与调用方式
/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */