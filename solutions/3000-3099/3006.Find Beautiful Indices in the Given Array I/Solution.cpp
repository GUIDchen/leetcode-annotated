// 题目：3006. 找出数组中的美丽下标 I（Find Beautiful Indices in the Given Array I）
// 核心思路：先用 KMP 分别求出两个模式串在 s 中的全部出现下标，把 B 的下标排序，再对每个 A 的出现位置用 lower_bound 缩出候选区间，检查是否存在距离不超过 k 的 B 下标。
// 时间复杂度：O(n + m + |A| · log|B|)，KMP 线性扫描加二分查找；空间复杂度：O(n + m)，存放两串的出现下标与前缀函数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> beautifulIndices(string s, string patternA, string patternB, int k) {  // s：主串；patternA/patternB：两个模式串；k：下标之差的绝对值上限
        vector<int> beautifulIndicesA = kmpSearch(s, patternA);  // KMP 求出 patternA 在 s 中所有出现的起始下标
        vector<int> beautifulIndicesB = kmpSearch(s, patternB);  // KMP 求出 patternB 在 s 中所有出现的起始下标

        sort(beautifulIndicesB.begin(), beautifulIndicesB.end());  // B 的出现下标本身就是递增的，排序只是为保证后面 lower_bound 的前提成立

        vector<int> result;  // 收集所有美丽下标
        for (int indexA : beautifulIndicesA) {  // 逐个考察 A 的每个出现位置
            int left = lower_bound(beautifulIndicesB.begin(), beautifulIndicesB.end(), indexA - k) - beautifulIndicesB.begin();  // 在 B 的下标数组里二分出第一个 >= indexA - k 的位置，作为左端点
            int right = lower_bound(beautifulIndicesB.begin(), beautifulIndicesB.end(), indexA + k + patternB.length()) - beautifulIndicesB.begin();  // 二分出第一个 >= indexA + k + len(patternB) 的位置，作为右端点（区间略宽，后面再精确判断）

            left = (left >= 0) ? left : -(left + 1);  // lower_bound 的返回值减首迭代器本来就非负，这里保留防御式写法保证下标不小于 0
            right = (right >= 0) ? right : -(right + 1);  // 同样保证右端点为非负下标

            for (int indexB = left; indexB < right; indexB++) {  // 在候选区间 [left, right) 内查找满足距离要求的 B 下标
                if (abs(beautifulIndicesB[indexB] - indexA) <= k) {  // 与 indexA 的距离不超过 k，满足「美丽」条件
                    result.push_back(indexA);  // 记录这个美丽下标
                    break;  // 找到一个就够，跳出内层循环
                }  // if 分支结束
            }  // 候选区间遍历结束
        }  // A 的所有出现位置处理完毕

        return result;  // 返回按升序排列的美丽下标
    }

private:  // 私有辅助函数区
    vector<int> kmpSearch(string text, string pattern) {  // KMP：返回 pattern 在 text 中出现的所有起始下标
        vector<int> indices;  // 保存所有匹配的起始下标
        vector<int> pi = computePrefixFunction(pattern);  // 先算出模式串的前缀函数（next 数组）

        int q = 0;  // q 表示当前已经匹配的模式串长度
        for (int i = 0; i < text.length(); i++) {  // 逐字符扫描主串
            while (q > 0 && pattern[q] != text[i]) {  // 失配时沿前缀函数回退，直到能继续匹配或 q 归零
                q = pi[q - 1];  // 回退到次长的相等前后缀长度
            }  // while 回退结束
            if (pattern[q] == text[i]) {  // 当前字符能与模式串下一位接上
                q++;  // 匹配长度加一
            }  // if 分支结束
            if (q == pattern.length()) {  // 匹配长度达到模式串长度，说明找到一次完整出现
                indices.push_back(i - q + 1);  // 起点是 i - q + 1
                q = pi[q - 1];  // 继续寻找可能重叠的下一次出现
            }  // if 分支结束
        }  // 主串扫描结束

        return indices;  // 返回全部出现下标
    }

    vector<int> computePrefixFunction(string pattern) {  // 计算前缀函数 pi[i]：pattern[0..i] 的最长相等前后缀长度
        int m = pattern.length();  // 模式串长度
        vector<int> pi(m, 0);  // pi 数组初始化为 0
        int k = 0;  // k 是当前已匹配的前缀长度
        for (int q = 1; q < m; q++) {  // 从第二个字符开始递推
            while (k > 0 && pattern[k] != pattern[q]) {  // 失配时沿 pi 回退
                k = pi[k - 1];  // 取次长的相等前后缀长度
            }  // while 回退结束
            if (pattern[k] == pattern[q]) {  // 字符相等，前缀长度可以加一
                k++;  // k 自增
            }  // if 分支结束
            pi[q] = k;  // 记录当前位置的最长相等前后缀长度
        }  // 递推循环结束
        return pi;  // 返回前缀函数数组
    }
};
