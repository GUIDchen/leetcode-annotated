// 3285. 找到稳定山的下标（Find Indices of Stable Mountains）
// 核心思路：稳定山就是「前一座山的高度严格大于阈值」的山；从下标 1 开始遍历，检查前一个位置的高度是否超过 threshold，满足就收集该下标。
// 复杂度：时间 O(n)，空间 O(1)（不计返回值）

class Solution {  // 定义题解类
public:  // 公开接口
    vector<int> stableMountains(vector<int>& height, int threshold) {  // 返回所有稳定山的下标（升序）
        vector<int> ans;  // 保存答案下标
        for (int i = 1; i < height.size(); ++i) {  // 从第 2 座山开始遍历，它前面一定有山
            if (height[i - 1] > threshold) {  // 前一座山的高度超过阈值，则当前山是稳定山
                ans.push_back(i);  // 记录当前下标
            }  // 结束稳定山判定
        }  // 结束遍历
        return ans;  // 返回所有稳定山的下标
    }  // 方法结束
};  // 类定义结束
