# map urls to views
from django.urls import path
from . import views

# URLConfiguration
urlpatterns = [
    path('', views.main)
]
