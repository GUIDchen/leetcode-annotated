// 题目：1183. 矩阵中 1 的最大数量（Maximum Number of Ones）
// 思路：把格子按 (i % x, j % x) 分成 x*x 个等价类（x = sideLength），同一个边长 x 的方阵恰好含各类各一个；
//       所以每个方阵最多放 maxOnes 个 1，等价于选 maxOnes 个格子数最多的类。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {  // width/height 为矩阵尺寸，sideLength 为方阵边长，maxOnes 为每个方阵内 1 的上限
        int x = sideLength;  // 简写周期长度，后面要反复取模
        vector<int> cnt(x * x);  // 把矩阵划分成 x*x 个等价类，cnt 记录每类格子个数
        for (int i = 0; i < width; ++i) {  // 枚举行下标
            for (int j = 0; j < height; ++j) {  // 枚举列下标
                int k = (i % x) * x + (j % x);  // 归类：坐标模 x 后相同，说明它们在任何边长 x 的方阵里位置一致、会互相挤占
                ++cnt[k];  // 该类格子数 +1
            }  // 列枚举结束
        }  // 行枚举结束
        sort(cnt.rbegin(), cnt.rend());  // 降序排序：出现次数多的等价类优先填 1，收益最大
        int ans = 0;  // ans 记录能放下的 1 的总数
        for (int i = 0; i < maxOnes; ++i) {  // 每个方阵最多 maxOnes 个 1，因此最多只能在 maxOnes 个等价类里放 1
            ans += cnt[i];  // 累加这些等价类的格子总数
        }  // 选取完毕
        return ans;  // 返回最大数量
    }  // 方法体结束
};  // 题解类结束