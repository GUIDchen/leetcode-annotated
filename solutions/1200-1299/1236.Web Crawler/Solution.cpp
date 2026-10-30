// 题目：1236. 网络爬虫（Web Crawler，会员题）
// 思路：从 startUrl 出发做深度优先搜索，用集合记录已访问 URL 防止重复，并且只递归与当前页面同域名（host 相同）的链接。
// 时间复杂度：O(V + E)，V 为可达页面数、E 为链接数；空间复杂度：O(V)，答案与访问集合各存 V 个 URL。
/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 成员对外可见
    vector<string> ans;  // 保存爬到的全部同域名 URL
    unordered_set<string> vis;  // 已访问过的 URL 集合，用来去重与防止环形链接死循环

    vector<string> crawl(string startUrl, HtmlParser htmlParser) {  // 入口：startUrl 是起点，htmlParser 是判题器提供的解析器
        dfs(startUrl, htmlParser);  // 从起点开始深度优先爬取
        return ans;  // 返回爬到的全部 URL
    }  // crawl 方法结束

    void dfs(string& url, HtmlParser& htmlParser) {  // 深度优先遍历：url 是当前页面，htmlParser 用来取它的外链
        if (vis.count(url)) return;  // 已经访问过就直接返回，避免重复入队与死循环
        vis.insert(url);  // 标记当前 URL 已访问
        ans.push_back(url);  // 当前 URL 计入答案
        for (string next : htmlParser.getUrls(url))  // 遍历当前页面的所有外链
            if (host(url) == host(next))  // 只递归与当前页面同域名（host 相同）的链接
                dfs(next, htmlParser);  // 递归处理该链接
    }  // dfs 方法结束

    string host(string url) {  // 提取 URL 中的域名部分，用于判断是否属于同一站点
        int i = 7;  // 跳过 "http://" 这 7 个字符
        string res;  // 用于累积域名
        for (; i < url.size(); ++i) {  // 从第 7 个字符扫描到字符串末尾
            if (url[i] == '/') break;  // 遇到路径分隔符 '/' 说明域名已经结束
            res += url[i];  // 把域名字符追加进结果
        }  // for 结束
        return res;  // 返回域名
    }  // host 方法结束
};  // 类定义结束