from django.shortcuts import render
from django.http import HttpResponse
from .forms import SaveForm


# Create your views here.

# request handler

def main(request):
    # get data from db
    form = SaveForm(request.POST)
    context = {
        temp: form.cleaned_data.get('tempString'),
    }
    return render(request, 'temp.html', context)
