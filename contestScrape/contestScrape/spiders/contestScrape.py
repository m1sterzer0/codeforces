import scrapy
import re

class contestScrape(scrapy.Spider) :
    name = "contestScrape"
    start_urls = [ f"https://codeforces.com/contest/{x}" for x in range(760,1096) ]

    def parse(self, response) :
        res = {}

        if "problem" in response.url :
            diff = response.xpath('//span[@class="tag-box" and @title="Difficulty"]/text()').extract_first()
            if diff : 
                diff = re.sub(r'[^\d]*(\d+).*',r'\1',diff.rstrip())
            else :
                diff = '???'
            res['type']     = "problem"
            res['url']      = response.url
            res['diff']     = diff
            yield res

        else :
            title    = response.xpath('/html/head/title/text()').extract_first()
            problems = response.xpath('//div[@class="datatable"]//table[@class="problems"]/tr/td[@class="id"]/a/@href').extract()
            res['type']     = "contest"
            res['title']    = title 
            res['problems'] = problems
            res['url']      = response.url
            yield res

            for p in problems :
                nextpage = 'https://codeforces.com' + p
                yield scrapy.Request(nextpage, callback=self.parse)






    



