// 题目：2456. 最流行的视频创作者（Most Popular Video Creator）
// 思路：用哈希表统计每位创作者的总播放量 cnt，并记录其播放量最高（同播放量取 id 字典序最小）的视频下标 d；
// 再求出最大总播放量，把总播放量等于它的创作者及其最佳视频 id 收集进答案。
// 时间复杂度：O(n)，三次线性扫描哈希表；空间复杂度：O(n)，哈希表存每位创作者的信息。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) {  // 三个平行数组：作者、视频 id、播放量
        unordered_map<string, long long> cnt;  // 哈希表：作者 → 其所有视频的总播放量（用 long long 防止累加溢出）
        unordered_map<string, int> d;  // 哈希表：作者 → 其播放量最高（并列时 id 字典序最小）的视频下标
        int n = ids.size();  // 视频总数
        for (int k = 0; k < n; ++k) {  // 依次遍历每个视频
            auto c = creators[k], id = ids[k];  // 取出当前视频的作者名与视频 id
            int v = views[k];  // 取出当前视频的播放量
            cnt[c] += v;  // 该作者的总播放量累加上当前视频的播放量
            if (!d.count(c) || views[d[c]] < v || (views[d[c]] == v && ids[d[c]] > id)) {  // 该作者还没记录，或当前视频播放量更高，或播放量相同但 id 字典序更小
                d[c] = k;  // 更新该作者的最佳视频下标为当前视频
            }
        }
        long long mx = 0;  // 所有创作者中的最高总播放量，初始为 0
        for (auto& [_, x] : cnt) {  // 结构化绑定遍历哈希表：_ 是作者名（此处用不到），x 是总播放量
            mx = max(mx, x);  // 不断取较大值，得到最大总播放量
        }
        vector<vector<string>> ans;  // 答案容器，每项形如 {作者, 最佳视频 id}
        for (auto& [c, x] : cnt) {  // 再次遍历哈希表，逐位创作者判断
            if (x == mx) {  // 该创作者的总播放量正好等于最大总播放量
                ans.push_back({c, ids[d[c]]});  // 把作者名与最佳视频 id 组成一项加入答案
            }
        }
        return ans;  // 返回所有总播放量最高的创作者（并列时全部返回）
    }
};