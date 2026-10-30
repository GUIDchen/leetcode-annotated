// 题目：1054. 距离相等的条形码（Distant Barcodes）
// 思路：统计每个条码的频次，按「频次降序、数值升序」排序，再把前一半依次放进偶数下标、其余放进奇数下标，相同条码必然不相邻。
// 时间复杂度：O(n log n)，排序为主；空间复杂度：O(n)，计数数组与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {  // barcodes：输入条码数组，返回重排后的数组
        int mx = *max_element(barcodes.begin(), barcodes.end());  // 找出最大值，用来确定计数数组的长度
        int cnt[mx + 1];  // 计数数组：cnt[v] 记录条码 v 出现的次数
        memset(cnt, 0, sizeof(cnt));  // 全部清零，避免使用未初始化的计数
        for (int x : barcodes) {  // 遍历每个条码
            ++cnt[x];  // 累加出现次数
        }  // 统计完成
        sort(barcodes.begin(), barcodes.end(), [&](int a, int b) {  // 按频率降序、同频时数值升序排序，频率最高的排最前面
            return cnt[a] > cnt[b] || (cnt[a] == cnt[b] && a < b);  // 次数多的优先；次数相同则小值优先，保证结果稳定
        });  // 排序结束，最频繁的条码在最前
        int n = barcodes.size();  // 条码总个数
        vector<int> ans(n);  // 答案数组，先按长度占位
        for (int k = 0, j = 0; k < 2; ++k) {  // 两轮填充：k=0 先填偶数下标，k=1 再填奇数下标
            for (int i = k; i < n; i += 2) {  // 第 k 轮从下标 k 开始，步长为 2，隔位放置
                ans[i] = barcodes[j++];  // 按排序顺序依次放进相隔一位的位置
            }  // 一轮填充结束
        }  // 两轮填充结束，相同条码被隔开一位，不会相邻
        return ans;  // 返回满足「相邻元素不同」的重排结果
    }  // 方法结束
};  // 类定义结束