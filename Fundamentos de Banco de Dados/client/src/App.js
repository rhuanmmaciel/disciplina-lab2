import React, { useState } from 'react'
import { Navigate, Route, Routes, useNavigate } from 'react-router-dom';
import './css/app.css'

import DirectorsGrid from './components/dashboard/grids/directors';
import MoviesGrid from './components/dashboard/grids/movies';
import ActorsGrid from './components/dashboard/grids/actors';

import Movie from './components/movie/movie'
import Header from './components/header/header'
import ChartsGrid from './components/dashboard/grids/charts';

export default function App() 
{
  function MoviesPage()
  {
    return (
      <>
        <Header />
        <div className='dashboard'>
          <MoviesGrid/>
        </div>
      </>
    )
  }

  function DirectorsPage()
  {
    return (
      <>
        <Header />
        <div className='dashboard'>
          <DirectorsGrid/>
        </div>
      </>
    )
  }

  function ActorsPage()
  {
    return (
      <>
        <Header />
        <div className='dashboard'>
          <ActorsGrid/>
        </div>
      </>
    )
  }

  function ChartsPage()
  {
    return (
      <>
        <Header />
        <div className='dashboard'>
          <ChartsGrid/>
        </div>
      </>
    )
  }

  return (
    <div className='app'>
      <Routes>
        <Route exact path='/' element={ <Navigate to='/movies'/> } />
        <Route path='/movie' element={<Movie />} />
        <Route path='/movies/*' element={<MoviesPage />}/>
        <Route path='/directors/*' element={<DirectorsPage />}/>
        <Route path='/actors/*' element={<ActorsPage />}/>
        <Route path='/charts/*' element={<ChartsPage />}/>
      </Routes>
    </div>
  )
}

