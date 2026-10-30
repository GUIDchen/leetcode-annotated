// 题目：1306. 跳跃游戏 III（Jump Game III）
// 核心思路：把下标看作图的节点，从 start 出发做 BFS，能走到值为 0 的下标就成功；访问过的下标改成 -1 标记。
// 时间复杂度：O(n)，每个下标最多入队一次；空间复杂度：O(n)，队列最多同时存放 n 个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canReach(vector<int>& arr, int start) {  // arr 是跳跃数组，start 是起点下标
        queue<int> q{{start}};  // BFS 队列，初始只放起点下标
        while (!q.empty()) {  // 队列非空就继续扩展
            int i = q.front();  // 取出队首下标
            q.pop();  // 弹出队首，避免重复处理
            if (arr[i] == 0) {  // 到达值为 0 的格子，说明可以抵达
                return true;  // 立即返回成功
            }
            int x = arr[i];  // 记下当前格子允许的跳跃步数
            arr[i] = -1;  // 把当前格子置为 -1，表示已访问
            for (int j : {i + x, i - x}) {  // 枚举向右、向左两个落点
                if (j >= 0 && j < arr.size() && ~arr[j]) {  // 落点未越界且未访问：~(-1) 为 0 即假
                    q.push(j);  // 把合法落点加入队列等待扩展
                }
            }
        }
        return false;  // 搜索完所有可达下标仍未遇到 0，返回失败
    }
};  // 类定义结束（文件末尾无换行，保持原样）