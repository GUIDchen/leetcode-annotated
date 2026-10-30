// 题目：2424. 最长上传前缀（Longest Uploaded Prefix）
// 思路：用哈希集合记录已上传编号，并维护当前已连续覆盖到的位置 r；每次插入后从 r+1 开始往后延伸，得到最长前缀长度。
// 时间复杂度：均摊 O(1)，每个编号最多被 while 推进一次；空间复杂度：O(n)，集合保存全部已上传编号。
class LUPrefix {  // 设计题类：维护已上传视频的最长前缀长度
public:  // 对外接口
    LUPrefix(int n) {  // 构造函数，n 是视频总数
    }  // 本实现不需要按 n 预分配空间，只用哈希集合与计数器，构造函数留空

    void upload(int video) {  // 上传编号为 video 的视频
        s.insert(video);  // 把编号放进哈希集合，标记为「已上传」
        while (s.count(r + 1)) {  // 只要前缀的下一个编号也已经上传
            ++r;  // 前缀长度就可以继续加一
        }
    }

    int longest() {  // 查询当前最长已上传前缀的长度
        return r;  // r 始终表示 1..r 全部已上传的最大 r
    }

private:  // 内部状态
    int r = 0;  // 当前最长已上传前缀长度，初始为 0
    unordered_set<int> s;  // 保存所有已上传的视频编号，便于 O(1) 判重
};

/**
 * Your LUPrefix object will be instantiated and called as such:
 * LUPrefix* obj = new LUPrefix(n);
 * obj->upload(video);
 * int param_2 = obj->longest();
 */  // 以上是题目给定的调用示例，保持原样