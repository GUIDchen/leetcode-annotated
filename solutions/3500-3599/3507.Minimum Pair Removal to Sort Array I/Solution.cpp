// 题目：3507. 移除最小数对使数组有序 I（Minimum Pair Removal to Sort Array I）
// 思路：按题意直接模拟。每轮先判断数组是否已非递减，否则在全部相邻对中找和最小（和相同时取最靠左）的一对，用它的和替换左端元素并删掉右端元素，直到数组非递减为止。
// 时间复杂度：O(n²)，每轮扫描相邻对与删除元素都是 O(n)，最多合并 n-1 轮；空间复杂度：O(n)，额外拷贝了一份数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumPairRemoval(vector<int>& nums) {  // nums：待处理数组；返回使数组非递减所需的最少合并次数
        vector<int> arr = nums;  // 拷贝一份，在副本上合并以免改动输入
        int ans = 0;  // 记录已执行的合并次数

        while (!isNonDecreasing(arr)) {  // 只要还不是非递减就继续合并
            int k = 0;  // k 记录最小相邻对的左端下标
            int s = arr[0] + arr[1];  // 先以最左边一对之和作为初始最小值

            for (int i = 1; i < arr.size() - 1; ++i) {  // 枚举其余的相邻对
                int t = arr[i] + arr[i + 1];  // 当前相邻对 (i, i+1) 的和
                if (s > t) {  // 出现更小的和
                    s = t;  // 更新最小和
                    k = i;  // 记录它的左端下标
                }  // 本对比较结束
            }  // 相邻对扫描完毕

            arr[k] = s;  // 用数对之和替换左端元素
            arr.erase(arr.begin() + (k + 1));  // 删除被合并掉的右端元素
            ++ans;  // 合并次数加一
        }  // 本轮合并结束

        return ans;  // 返回最少合并次数
    }  // 方法结束

private:  // 私有辅助函数区域
    bool isNonDecreasing(const vector<int>& arr) {  // 判断数组是否已非递减（允许相等）
        for (int i = 1; i < (int) arr.size(); ++i) {  // 从第二个元素开始与前一元素比较
            if (arr[i] < arr[i - 1]) {  // 出现下降说明不满足非递减
                return false;  // 立即返回 false
            }  // 本对比较结束
        }  // 全部比较完毕
        return true;  // 全程无下降，数组已非递减
    }  // 方法结束
};  // 类定义结束
