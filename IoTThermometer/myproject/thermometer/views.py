from django.shortcuts import render
from django.http import HttpResponse
# Create your views here.

#request handler
def main(request):
    #get data from db
    return render(request,'temp.html',{
        'temp':'30'
    })