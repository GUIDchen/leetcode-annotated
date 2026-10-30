// 题目：1298. 你能从盒子里获得的最大糖果数（Maximum Candies You Can Get from Boxes）
// 思路：BFS。has 记录已经到手的盒子，took 记录已经开过并计过糖果的盒子；队列里只放已打开的盒子。
// 时间复杂度：O(n + 钥匙总数 + 盒中盒总数)；空间复杂度：O(n)，两个集合加一个队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxCandies(  // 返回能获得的最大糖果数
        vector<int>& status,  // status[i]：第 i 个盒子是否已经打开
        vector<int>& candies,  // candies[i]：第 i 个盒子里的糖果数
        vector<vector<int>>& keys,  // keys[i]：第 i 个盒子里的钥匙能打开的盒子编号
        vector<vector<int>>& containedBoxes,  // containedBoxes[i]：第 i 个盒子里装的盒子编号
        vector<int>& initialBoxes) {  // initialBoxes：一开始就拥有的盒子编号
        queue<int> q;  // 待处理的「已打开」盒子
        unordered_set<int> has, took;  // has：已经到手的盒子；took：已经开过并计过糖果的盒子
        int ans = 0;  // 已获得的糖果总数

        for (int box : initialBoxes) {  // 先把初始拥有的盒子全部登记为到手
            has.insert(box);  // 记录到手
            if (status[box]) {  // 初始就是打开的盒子可以立刻打开
                q.push(box);  // 放进队列等待处理
                took.insert(box);  // 标记为已打开，避免重复计分
                ans += candies[box];  // 拿走盒中糖果
            }
        }

        while (!q.empty()) {  // 还有能打开的盒子就继续扩展
            int box = q.front();  // 取出队首盒子
            q.pop();  // 弹出队首

            for (int k : keys[box]) {  // 处理这个盒子里的所有钥匙
                if (!status[k]) {  // 钥匙对应的盒子之前是锁着的
                    status[k] = 1;  // 用钥匙把它打开
                    if (has.count(k) && !took.count(k)) {  // 该盒子已到手且还没开过
                        q.push(k);  // 可以立即打开，入队
                        took.insert(k);  // 标记为已打开
                        ans += candies[k];  // 拿走糖果
                    }
                }
            }

            for (int b : containedBoxes[box]) {  // 处理这个盒子里装的所有盒子
                has.insert(b);  // 盒中盒到手
                if (status[b] && !took.count(b)) {  // 已经能用钥匙打开且还没处理过
                    q.push(b);  // 入队
                    took.insert(b);  // 标记为已打开
                    ans += candies[b];  // 拿走糖果
                }
            }
        }

        return ans;  // 返回累计获得的糖果数
    }
};
