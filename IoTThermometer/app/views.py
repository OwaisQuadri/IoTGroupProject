from django.shortcuts import render
from django.http import HttpResponse,JsonResponse
from .forms import SaveForm
from rest_framework.parsers import JSONParser
from rest_framework.renderers import JSONRenderer
from .models import Temperature
from .serializers import TempSerializer
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status
from rest_framework.views import APIView

# Create your views here.
class History(APIView):
    def get(self, request):
        temps = Temperature.objects.all()
        ser=TempSerializer(temps, many=True)
        context={
            'historyJSON': ser.data
        }
        return render(request, 'history.html',context)

class Home(APIView):
    def get(self,request):
        temp=Temperature.objects.last().temperature
        humidity=Temperature.objects.last().humidity
        # ser=TempSerializer(temp)
        # currTemp=ser.data
        print(temp," ",humidity)
        context={
            'temp': temp,
            'humidity':humidity
        }
        return render(request, 'temp.html',context)