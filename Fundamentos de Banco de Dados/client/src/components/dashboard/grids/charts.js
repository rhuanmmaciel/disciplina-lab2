import { useState, useEffect } from "react"
import { Pie } from 'react-chartjs-2';
import { Chart as  ChartJS } from 'chart.js/auto';
import axios from "axios"

export default function ChartsGrid()
{
  const [moviesGender, setMoviesGender] = useState(
  [
    { label: "homens em filmes", value: 1 },
    { label: "mulheres em filmes", value: 1 }
  ])

  const [chartData, setChartData] = useState({
    labels: moviesGender.map(movie => movie.label),
    datasets: 
    [{
      label: "value",
      data: moviesGender.map(movie => movie.value),
    }]
  })

  useEffect(() => 
  {
    setChartData({
      labels: moviesGender.map(movie => movie.label),
      datasets: 
      [{
        label: "value",
        data: moviesGender.map(movie => movie.value),
      }]
    })
    
  }, [moviesGender])

  useEffect(() => 
  {
    console.log(moviesGender);

    axios.get('http://localhost:9000/charts/gender')
      .then(res => 
      {
        const newMoviesGender = [...moviesGender]

        newMoviesGender[0].value = res.data[0].total_homens;
        newMoviesGender[1].value = res.data[0].total_mulheres;

        setMoviesGender(newMoviesGender); 
        console.log(newMoviesGender)
      })
      .catch(err => {console.log(err)})
  }, [])

  function PieChart({ chartData })
  {
    return <Pie data={ chartData }/>
  }

  return (
    <div className="charts">
      <PieChart chartData={ chartData }/>
    </div>
  )
}