// 题目：573. 松鼠模拟（Squirrel Simulation）
// 核心思路：假设松鼠每次都从树上出发，总路程为所有坚果往返树的 2 倍；再枚举第一颗坚果，把该趟改成从松鼠位置出发。
// 时间复杂度：O(n)，只需两趟遍历坚果；空间复杂度：O(1)，只用常数额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDistance(int height, int width, vector<int>& tree, vector<int>& squirrel, vector<vector<int>>& nuts) {  // height/width 为网格尺寸，tree/squirrel 为坐标，nuts 为各坚果坐标
        int tr = tree[0], tc = tree[1];  // 取出树的行列坐标，后续反复使用
        int sr = squirrel[0], sc = squirrel[1];  // 取出松鼠的行列坐标，只用于第一趟
        int s = 0;  // 累计「每颗坚果都从树出发再回树」的总路程
        for (const auto& e : nuts) {  // 遍历所有坚果
            s += abs(e[0] - tr) + abs(e[1] - tc);  // 曼哈顿距离：坚果到树的行差加列差
        }  // 单趟求和结束
        s <<= 1;  // 左移一位等价乘 2：每颗坚果都要「去 + 回」，所以路程要翻倍
        int ans = INT_MAX;  // 记录最优总路程，初始化为最大整数
        for (const auto& e : nuts) {  // 枚举哪一颗坚果作为第一颗搬运
            int a = abs(e[0] - tr) + abs(e[1] - tc);  // 该坚果到树的距离，即原方案里的一趟
            int b = abs(e[0] - sr) + abs(e[1] - sc);  // 松鼠到该坚果的距离，即新方案里的一趟
            ans = min(ans, s - a + b);  // 用 b 替换掉 a，得到该首颗坚果下的总路程，取最小
        }  // 枚举结束
        return ans;  // 返回最小总路程
    }  // minDistance 结束
};  // 类定义结束
