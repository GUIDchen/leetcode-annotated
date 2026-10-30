// 3830. 移除至多一个元素后的最长交替子数组 / Longest Alternating Subarray After Removing At Most One Element（困难）
// 核心思路：预处理四个数组——l1/l2 表示以 i 结尾且最后一步上升/下降的最长交替长度，r1/r2 表示以 i 开头且第一步上升/下降的最长交替长度；再枚举被删除的位置 i，把左右两段拼起来。
// 复杂度：四次线性扫描，时间 O(n)，空间 O(n)。
class Solution {  // 求删除至多一个元素后最长的交替（锯齿形）子数组长度
public:  // 对外接口区
    int longestAlternating(vector<int>& nums) {  // 返回删除至多一个元素后最长交替子数组的长度（相邻元素大小关系严格交替）
        int n = nums.size();  // 数组长度
        vector<int> l1(n, 1), l2(n, 1), r1(n, 1), r2(n, 1);  // 四个 DP 数组，默认长度 1：l 表示以 i 结尾，r 表示以 i 开头；1 表示上升步，2 表示下降步

        int ans = 0;  // 答案初始为 0，后面用正向扫描与删除枚举不断更新

        for (int i = 1; i < n; i++) {  // 从左到右预处理“以 i 结尾”的交替长度
            if (nums[i - 1] < nums[i]) {  // 最后一步上升
                l1[i] = l2[i - 1] + 1;  // 接在以 i-1 结尾、最后一步下降的序列后面
            } else if (nums[i - 1] > nums[i]) {  // 最后一步下降
                l2[i] = l1[i - 1] + 1;  // 接在以 i-1 结尾、最后一步上升的序列后面
            }
            ans = max(ans, l1[i]);  // 更新答案：不删除元素、以 i 结尾且最后一步上升的情况
            ans = max(ans, l2[i]);  // 同上，考虑以 i 结尾且最后一步为下降的情况
        }

        for (int i = n - 2; i >= 0; i--) {  // 从右到左预处理“以 i 开头”的交替长度
            if (nums[i + 1] > nums[i]) {  // 第一步上升（i → i+1 递增）
                r1[i] = r2[i + 1] + 1;  // 后面必须紧跟下降步，故接 r2[i+1]
            } else if (nums[i + 1] < nums[i]) {  // 第一步下降（i → i+1 递减）
                r2[i] = r1[i + 1] + 1;  // 后面必须紧跟上升步，故接 r1[i+1]
            }
        }

        for (int i = 1; i < n - 1; i++) {  // 枚举要删除的位置 i（首尾不能删，作为哨兵保留）
            if (nums[i - 1] < nums[i + 1]) {  // 删除 i 后 nums[i-1] 与 nums[i+1] 之间是上升关系
                ans = max(ans, l2[i - 1] + r2[i + 1]);  // 左侧须以下降步结尾、右侧须以下降步开头，拼接后恰好交替
            } else if (nums[i - 1] > nums[i + 1]) {  // 删除 i 后衔接处是下降关系
                ans = max(ans, l1[i - 1] + r1[i + 1]);  // 左侧须以上升步结尾、右侧须以上升步开头
            }
        }

        return ans;  // 返回最长交替子数组长度
    }
};
