# 题目：1236. 网络爬虫（Web Crawler，会员题）
# 思路：从 startUrl 深度优先爬取，用 set 记录已访问的 URL，且只递归爬取与当前页面同域名的链接。
# 时间复杂度：O(V + E)，V 是可达页面数、E 是链接数；空间复杂度：O(V)，结果集合存 V 个 URL。
# """
# This is HtmlParser's API interface.
# You should not implement it, or speculate about its implementation
# """
# class HtmlParser(object):
#    def getUrls(self, url):
#        """
#        :type url: str
#        :rtype List[str]
#        """


class Solution:  # LeetCode 约定的题解类
    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:  # 入口：startUrl 是起点，htmlParser 是判题器提供的解析器
        def host(url):  # 内部函数：截取 URL 的域名部分
            url = url[7:]  # 切片跳过 "http://" 这 7 个字符
            return url.split('/')[0]  # 第一个 '/' 之前就是域名

        def dfs(url):  # 内部函数：深度优先爬取
            if url in ans:  # 已经访问过就返回，防止重复与死循环
                return  # 结束本次递归
            ans.add(url)  # 标记该 URL 已访问并计入结果
            for next in htmlParser.getUrls(url):  # 遍历当前页面的所有外链
                if host(url) == host(next):  # 只处理与当前页面同域名的链接
                    dfs(next)  # 递归爬取该链接

        ans = set()  # 结果集合，天然去重（dfs 中以闭包方式引用）
        dfs(startUrl)  # 从起点开始爬
        return list(ans)  # 集合转列表后返回
