// 3629. 通过质数传送到达终点的最少跳跃次数 / Minimum Jumps to Reach End via Prime Teleportation
// 核心思路：线性筛预处理每个数的质因子，把含有同一质因子的下标连成传送边，再按层 BFS 求最少跳跃次数
// 时间复杂度 O(mx log log mx + n·ω)，空间复杂度 O(mx log log mx + n)，其中 ω 为质因子个数
//
const int mx = 1e6 + 1;  // mx 为数值上限 1e6 加一，下标可直接用 1..1e6
vector<int> factors[mx];  // factors[x] 保存 x 的所有质因子

int init = [] {  // 全局静态 lambda：程序启动时一次性完成质因子预处理
    for (int i = 2; i < mx; ++i) {  // 从小到大枚举候选质因子 i
        if (factors[i].empty()) {  // factors[i] 为空说明 i 没被更小的质数标记过，即 i 是质数
            for (int j = i; j < mx; j += i) {  // 用质数 i 去筛它的所有倍数 j
                factors[j].push_back(i);  // 把质因子 i 追加到 j 的因子列表中
            }  // 内层 for 结束
        }  // if 结束
    }  // 外层 for 结束
    return 0;  // lambda 返回 0，仅用于触发静态初始化
}();  // 立即调用该 lambda，预处理只做一次

class Solution {  // 题目要求实现的类
public:  // 对外接口
    int minJumps(vector<int>& nums) {  // 返回从下标 0 跳到下标 n-1 的最少跳跃次数
        int n = nums.size();  // n 为数组长度
        unordered_map<int, vector<int>> g;  // g[p] 记录所有含有质因子 p 的下标，等价于传送图
        for (int i = 0; i < n; i++) {  // 遍历每个下标
            int x = nums[i];  // 取出当前下标对应的数值
            for (int p : factors[x]) {  // 枚举该数值的每个质因子
                g[p].push_back(i);  // 把下标 i 挂到质因子 p 的传送列表上
            }  // 内层 for 结束
        }  // 外层 for 结束，传送图构建完成
        int ans = 0;  // ans 记录当前 BFS 层数，也就是跳跃次数
        vector<bool> vis(n, false);  // vis 标记下标是否已经访问过
        vis[0] = true;  // 起点 0 标记为已访问
        queue<int> q;  // 队列存放当前层的下标
        q.push(0);  // 起点入队
        while (true) {  // 按层 BFS 扩展，终点一定会被到达
            queue<int> nq;  // nq 收集下一层的下标
            while (!q.empty()) {  // 处理当前层的全部下标
                int i = q.front();  // 取出队首下标
                q.pop();  // 弹出队首
                if (i == n - 1) {  // 到达最后一个下标即抵达终点
                    return ans;  // 返回当前层数作为最少跳跃次数
                }  // if 结束
                vector<int> idx = g[nums[i]];  // 取出该数值能传送到的所有下标（复制一份，避免下面 push 影响原图）
                idx.push_back(i + 1);  // 总是可以向后走一步到 i+1
                if (i > 0) {  // 如果不在数组首元素
                    idx.push_back(i - 1);  // 就可以向前走一步到 i-1
                }  // if 结束
                for (int j : idx) {  // 枚举所有一步可到达的下标
                    if (!vis[j]) {  // 只扩展还没访问过的下标
                        vis[j] = true;  // 标记为已访问，防止重复入队
                        nq.push(j);  // 加入下一层队列
                    }  // if 结束
                }  // for 结束
                g[nums[i]].clear();  // 清空该质因子的传送列表，后续无需再次枚举
            }  // while 结束
            q = nq;  // 把下一层作为新的当前层
            ans++;  // 跳跃次数加一
        }  // 外层 while 结束
    }  // 函数结束
};  // 类定义结束
