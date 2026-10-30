// 3846. 使用单指输入字符串的总距离 / Total Distance to Type a String Using One Finger（中等）
// 核心思路：预先建好 QWERTY 键盘的字母坐标表，再按序累加手指从上一键到下一键的曼哈顿距离。
// 复杂度：时间 O(|s|)，空间 O(1)。
class Solution {  // 解题类：LeetCode 判题器约定的类名
public:  // 公有接口
    int totalDistance(string s) {  // 返回从起始键 'a' 出发、按顺序敲出 s 的总移动距离
        static unordered_map<char, pair<int, int>> pos = [] {  // 静态缓存每个字母的键盘坐标，只在首次调用时构建
            unordered_map<char, pair<int, int>> m;  // 局部表：字母到 (行, 列) 的映射
            vector<string> keys = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};  // 键盘三行布局
            for (int i = 0; i < keys.size(); ++i) {  // 逐行遍历
                for (int j = 0; j < keys[i].size(); ++j) {  // 逐列遍历
                    m[keys[i][j]] = {i, j};  // 记录该字母所在的行列坐标
                }  // 列遍历结束
            }  // 行遍历结束
            return m;  // 返回构建好的坐标表
        }();  // 立即执行该 lambda 完成初始化

        char pre = 'a';  // pre 记录手指当前所在的字母，初始在 'a'
        int ans = 0;  // ans 累计移动距离

        for (char cur : s) {  // 依次敲击每个字符
            auto [x1, y1] = pos[pre];  // 当前手指所在键的坐标
            auto [x2, y2] = pos[cur];  // 目标键的坐标
            ans += abs(x1 - x2) + abs(y1 - y2);  // 累加两键之间的曼哈顿距离
            pre = cur;  // 手指移动到目标键，成为下一次的起点
        }  // 遍历结束

        return ans;  // 返回总移动距离
    }  // totalDistance 方法结束
};  // 解题类定义结束