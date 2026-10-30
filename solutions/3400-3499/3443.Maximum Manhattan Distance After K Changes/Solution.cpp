// 3443. K 次修改后的最大曼哈顿距离 / Maximum Manhattan Distance After K Changes
// 核心思路：曼哈顿距离可拆成两对方向分量，四种组合分别计算；遍历时目标方向 +1，其余方向优先用 k 次修改转成 +1，否则 -1，取最大前缀和。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有方法
    int maxDistance(string s, int k) {  // 返回最多修改 k 个字符后的最大曼哈顿距离
        auto calc = [&](char a, char b) {  // 计算以 a、b 两个方向为目标组合时的最大距离
            int ans = 0, mx = 0, cnt = 0;  // ans 为历史最大，mx 为当前得分，cnt 为已用修改次数
            for (char c : s) {  // 顺序遍历移动指令
                if (c == a || c == b) {  // 属于目标方向组合，本分量加一
                    ++mx;  // 当前得分加一
                } else if (cnt < k) {  // 其余方向且还有修改次数
                    ++mx;  // 改成目标方向，得分加一
                    ++cnt;  // 已用修改次数加一
                } else {  // 修改次数已用完
                    --mx;  // 反向移动使得分减一
                }  // 结束方向判断
                ans = max(ans, mx);  // 更新历史最优
            }  // 结束遍历
            return ans;  // 返回该组合的最优值
        };  // 结束 lambda 定义
        int a = calc('S', 'E');  // 下 + 右 组合
        int b = calc('S', 'W');  // 下 + 左 组合
        int c = calc('N', 'E');  // 上 + 右 组合
        int d = calc('N', 'W');  // 上 + 左 组合
        return max({a, b, c, d});  // 四种组合取最大值
    }  // 结束 maxDistance 方法
};  // 结束 Solution 类
