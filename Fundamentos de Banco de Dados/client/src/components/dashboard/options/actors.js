import { useRef } from "react"
import { useLocation, useNavigate } from 'react-router-dom';

export default function ActorsOptions() 
{
  const navigate = useNavigate();

  const nameRef = useRef();
  const genderMaleRef = useRef();
  const genderFemaleRef = useRef();
  const ethnicityRef = useRef();
  const heightMinRef = useRef();
  const heightMaxRef = useRef();

  function sortName(order)
  {
    const newQuery = `/actors/order/name?order=${order}`;
    navigate(newQuery)
  }

  function sortHeight(order)
  {
    const newQuery = `/actors/order/height?order=${order}`;
    navigate(newQuery)
  }

  function filterName()
  {
    const newQuery = `/actors/filter/name?actorName=${nameRef.current.value}`;
    navigate(newQuery);
  }

  function filterGender(gender)
  {
    const newQuery = `/actors/filter/gender?gender=${gender}`;
    navigate(newQuery);
  }

  function filterEthnicity()
  {
    const newQuery = `/actors/filter/ethnicity?ethnicity=${ethnicityRef.current.value}`;
    navigate(newQuery);
  }

  function filterHeight()
  {
    const newQuery = `/actors/filter/height?height1=${heightMinRef.current.value}&height2=${heightMaxRef.current.value}`;
    navigate(newQuery);
  }


  function filter()
  {
    if (nameRef.current.value !== '')
      filterName();

    else if (genderMaleRef.current.checked)
      filterGender(genderMaleRef.current.value)

    else if (genderFemaleRef.current.checked)
      filterGender(genderFemaleRef.current.value)

    else if (ethnicityRef.current.value !== '')
      filterEthnicity();

    else if (heightMinRef.current.value !== '' || heightMaxRef.current.value !== '')
    {
      if (heightMinRef.current.value === '')
        heightMinRef.current.value = 100

      if (heightMaxRef.current.value === '')
        heightMaxRef.current.value = 250
      
      filterHeight();
    }
  }

  return (
    <div className="options">
      <div className="options__sort">
        <div className="options__sort--title">SORT</div>
        <div className="options__sort__list">
          <div className="options__sort--name">
            <div className="option" onClick={() => { sortName('ASC') }}>Name (A-Z)</div>
            <div className="option" onClick={() => { sortName('DESC') }}>Name (Z-A)</div>
          </div>

          <div className="options__sort--height">
            <div className="option">Age Ascending</div>
            <div className="option">Age Descending</div>
          </div>

          <div className="options__sort--release">
            <div className="option" onClick={ () => {sortHeight('ASC')} }>Height Ascending</div>
            <div className="option" onClick={ () => {sortHeight('DESC')} }>Height Descending</div>
          </div>

          <div className="options__sort--gross">
            <div className="option">Net worth Ascending</div>
            <div className="option">Net worth Descending</div>
          </div>
        </div>
      </div>

      <div className="options__filter">
        <div className="options__filter--title">FILTER</div>
        <div className="options__filter__list">
          <div className="options__filter--name">
            <div className="option">Name</div>
            <input className="option--input" ref={ nameRef } type="text" name="name" id="name"/>
          </div>

          <div className="options__filter--gender">
            <div className="option">Gender</div>
            <label className="radio"><input type="radio" ref={ genderMaleRef } name="gender" value="Male"/>Male</label>
            <label className="radio"><input type="radio" ref={ genderFemaleRef } name="gender" value="Female"/>Female</label>
          </div>

          <div className="options__filter--director">
            <div className="option">Ethnicity</div>
            <input className="option--input" ref={ ethnicityRef } type="text" name="director" id="director"/>
          </div>

          <div className="options__filter--release">
            <div className="option">Age</div>
            <input className="option--input" type="number" name="release_from" id="release_from" placeholder="from"/>
            <input className="option--input" type="number" name="release_to" id="release_to" placeholder="to"/>
          </div>

          <div className="options__filter--rating">
            <div className="option">Height</div>
            <input className="option--input" ref={ heightMinRef } type="number" name="rating_from" id="rating_from" placeholder="from (meters)"/>
            <input className="option--input" ref={ heightMaxRef } type="number" name="rating_to" id="rating_to" placeholder="to (meters)"/>
          </div>
        </div>
      </div>

      <div className="options__submit" onClick={ filter }>SEARCH</div>
    </div>
  )
}