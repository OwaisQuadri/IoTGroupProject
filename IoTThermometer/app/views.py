from django.shortcuts import render
from django.http import HttpResponse,JsonResponse
from .forms import SaveForm
from rest_framework.parsers import JSONParser
from rest_framework.renderers import JSONRenderer
from .models import Temperature
from .serializers import TempSerializer

# Create your views here.

# request handler

def main(request):
    # get data from db
    form = SaveForm(request.POST)
    context = {
        temp: form.cleaned_data.get('tempString'),
    }
    return render(request, 'temp.html', context)

def temp_list(request):
    if request.method =='GET':
        temps = Temperature.objects.all()
        
        ser=TempSerializer(temps, many=True)
        return JsonResponse(ser.data, safe = False)

    elif request.method =='POST':
        data = JSONParser.parse(request)
        ser=TempSerializer(data=data)
        if ser.is_valid():
            ser.save()
            return JsonResponse(ser.data,status=201)
        return JsonResponse(ser.errors,status=400)