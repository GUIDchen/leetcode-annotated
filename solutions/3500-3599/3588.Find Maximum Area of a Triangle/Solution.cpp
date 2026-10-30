// 3588. 找到最大三角形面积（Find Maximum Area of a Triangle）
// 核心思路：三角形需要一条水平（或竖直）底边，按 x 分组记录每组 y 的最小与最大值得到底边，再乘该组到最左/最右 x 的最大水平高；转置坐标再算一次取较大值。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为坐标点个数。
class Solution {  // 定义题解类
public:  // 公有接口，判题器从这里调用
    long long maxArea(vector<vector<int>>& coords) {  // 求所有点能组成的最大三角形面积（返回值是面积的两倍）
        auto calc = [&]() -> long long {  // 按当前坐标轴方向计算一次最大面积
            int mn = INT_MAX, mx = 0;  // 记录最小的 x 与最大的 x
            unordered_map<int, int> f, g;  // f 存每列最小 y，g 存每列最大 y
            for (auto& c : coords) {  // 遍历所有坐标点
                int x = c[0], y = c[1];  // 取出横纵坐标
                mn = min(mn, x);  // 更新最小 x
                mx = max(mx, x);  // 更新最大 x
                if (f.count(x)) {  // 该 x 已经出现过，需要比较 y
                    f[x] = min(f[x], y);  // 更新同列最小 y
                    g[x] = max(g[x], y);  // 更新同列最大 y
                } else {  // 该 x 首次出现
                    f[x] = y;  // 初始化同列最小 y
                    g[x] = y;  // 初始化同列最大 y
                }  // 结束分支
            }  // 结束坐标遍历
            long long ans = 0;  // 记录本次计算的最大面积
            for (auto& [x, y] : f) {  // 枚举用作竖直底边的每一列
                int d = g[x] - y;  // 该列上最长竖直底边的长度
                ans = max(ans, 1LL * d * max(mx - x, x - mn));  // 底边乘该列到最左/最右 x 的最大水平高
            }  // 结束枚举
            return ans;  // 返回本次计算的最大面积
        };  // 结束 lambda

        long long ans = calc();  // 先按原始坐标轴计算一次
        for (auto& c : coords) {  // 遍历所有点做坐标交换
            swap(c[0], c[1]);  // 交换横纵坐标，等价于沿对角线转置
        }  // 结束交换
        ans = max(ans, calc());  // 转置后再算一次并取较大值
        return ans > 0 ? ans : -1;  // 面积为 0 说明无法构成三角形，返回 -1
    }  // 结束函数
};  // 结束类定义
