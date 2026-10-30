// 题目：244. 最短单词距离 II（Shortest Word Distance II）
// 思路：构造时建立「单词 → 全部下标」的索引；查询时对两个有序下标列表做双指针归并，每步比较后移动较小的一侧。
// 时间复杂度：构造 O(n)，每次查询 O(a + b)（a、b 为两词出现次数）；空间复杂度：O(n)，存下所有单词的下标。
class WordDistance {  // 预处理单词列表，支持多次最短距离查询
public:  // 构造函数对外可见
    WordDistance(vector<string>& wordsDict) {  // 构造函数：一次性建立「单词 → 出现的所有下标」索引
        for (int i = 0; i < wordsDict.size(); ++i) {  // 遍历整个单词列表
            d[wordsDict[i]].push_back(i);  // 把当前下标追加到该单词对应的下标列表
        }
    }

    int shortest(string word1, string word2) {  // 查询两个单词的最短距离
        auto a = d[word1], b = d[word2];  // 取出两个单词各自的下标列表（值拷贝，操作副本不影响索引）
        int i = 0, j = 0;  // 两个有序下标列表的游标
        int ans = INT_MAX;  // 最小距离，先置为无穷大
        while (i < a.size() && j < b.size()) {  // 双指针归并式扫描，两个列表都还没走完
            ans = min(ans, abs(a[i] - b[j]));  // 用当前这一对下标差更新最小距离
            if (a[i] <= b[j]) {  // 下标较小的一侧后移，才可能找到更近的一对
                ++i;  // 左列表游标右移
            } else {  // 否则右列表游标已更小
                ++j;  // 右列表游标右移
            }
        }  // 返回最小距离
        return ans;
    }

private:  // 以下为内部索引
    unordered_map<string, vector<int>> d;  // 单词 → 它出现的所有下标（天然升序）
};  // 类定义结束

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(wordsDict);
 * int param_1 = obj->shortest(word1,word2);
 */