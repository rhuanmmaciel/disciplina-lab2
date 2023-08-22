const Movie = require('../Models/movie.js');
const { Op } = require('sequelize');
const sequelize = require('../Models/db').sequelize;



function getPaginationParams(req) 
{
  const page = Number(req.query.page) || 1;
  let pageSize;

  if (req.query.pageSize <= 20)
    pageSize = Number(req.query.pageSize) || 10
  else
    pageSize = 20;


  return {
    page,
    pageSize,
  };
}

async function listarFilmes(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
        SELECT * 
        FROM movie m
        JOIN director d on(m.directorId = d.directorId)
        ORDER BY m.noOfVotes DESC
        LIMIT ${pageSize}
        OFFSET ${offset}
    `;

  const movies = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });
  res.json(movies);


}
async function FilmesGeneroDoAtor(req, res)
{
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;
  const query = `
    SELECT m.*, d.directorName
    FROM movie m 
    JOIN director d ON (m.directorId = d.directorId)
    JOIN cast c ON (m.movieId = c.movieId)
    JOIN actor a ON (c.actorID = a.actorID)
    WHERE a.actorSex = '${req.query.atorGender}'
    LIMIT ${pageSize}
    OFFSET ${offset}
  `;

  const movies = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });
  res.json(movies);
}

async function moviesOrderIMDBR(req, res) 
{

  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
        SELECT * 
        FROM movie m
        JOIN director d on(m.directorId = d.directorId) 
        ORDER BY IMDBRating ${req.query.order}
        LIMIT ${pageSize}
        OFFSET ${offset}
    `;

  const movies = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });
  res.json(movies);
}

async function moviesOrderGross(req, res)
{
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
        SELECT * 
        FROM movie m
        JOIN director d on(m.directorId = d.directorId) 
        ORDER BY gross ${req.query.order}
        LIMIT ${pageSize}
        OFFSET ${offset}
    `;

  const movies = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });
  res.json(movies);
}

async function moviesOrderRuntime(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);

  const movies = await Movie.findAll({
    order:
      [
        ['runtime', req.query.order]
      ],
    limit: pageSize,
    offset: (page - 1) * pageSize,
  });
  res.json(movies);
}

async function moviesOrderYear(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);


  const movies = await Movie.findAll({
    order:
      [
        ['releasedYear', req.query.order]
      ],
    limit: pageSize,
    offset: (page - 1) * pageSize,
  });
  res.json(movies);
}


async function moviesOrderName(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);

  const movies = await Movie.findAll({
    order:
      [
        ['title', req.query.order]
      ],
    limit: pageSize,
    offset: (page - 1) * pageSize,
  });
  res.json(movies);
}


async function nameMovies(req, res) 
{

  const { page, pageSize } = getPaginationParams(req);

  const totalCount = await Movie.count({
    where: {
      title: {
        [Op.like]: `%${req.query.title}%`
      }
    }
  });

  const totalPages = Math.ceil(totalCount / pageSize);

  let adjustedPage = page;
  if (page > totalPages)
    adjustedPage = totalPages;


  const movies = await Movie.findAll({
    where: {
      title: {
        [Op.like]: `%${req.query.title}%`
      }
    },
    limit: pageSize,
    offset: (adjustedPage - 1) * pageSize
  });

  res.json(movies);


}

async function filterIdMovie(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;
  const id_movie = req.query.idMovie;

  const query = `
      SELECT  m.*, GROUP_CONCAT(a.actorName) AS actorNames, d.directorName
      FROM movie m 
      JOIN director d ON (m.directorId = d.directorId)
      JOIN cast c ON (m.movieId = c.movieId)
      JOIN actor a ON (c.actorID = a.actorID)
      WHERE m.movieId = ${id_movie}
      GROUP BY m.movieId
      `;

  const movies = await sequelize.query(query, {
    replacements: { id_movie, pageSize, offset },
    type: sequelize.QueryTypes.SELECT
  });

  if (movies.length === 0 && page > 1)
    return res.redirect(`/id/filme?idMovie=${id_movie}&page=1&pageSize=${pageSize}`);

  res.json(movies);


}


async function releasedYearMovies(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);

  const totalCount = await Movie.count({
    where: {
      releasedYear: {
        [Op.between]: [req.query.ano1, req.query.ano2]
      }
    }
  });

  const totalPages = Math.ceil(totalCount / pageSize);

  let adjustedPage = page;
  if (page > totalPages)
    adjustedPage = totalPages;

  const movies = await Movie.findAll({
    where: {
      releasedYear: {
        [Op.between]: [req.query.ano1, req.query.ano2]
      }
    },
    limit: pageSize,
    offset: (adjustedPage - 1) * pageSize
  });

  res.json(movies);
}


async function ratingMovies(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);

  const totalCount = await Movie.count({
    where: {
      IMDBRating: {
        [Op.between]: [req.query.rating1, req.query.rating2]
      }
    }
  });

  const totalPages = Math.ceil(totalCount / pageSize);

  let adjustedPage = page;
  if (page > totalPages)
    adjustedPage = totalPages;

  const movies = await Movie.findAll({
    where: {
      IMDBRating: {
        [Op.between]: [req.query.rating1, req.query.rating2]
      }
    },
    limit: pageSize,
    offset: (adjustedPage - 1) * pageSize
  });

  res.json(movies);
}



async function atorMovies(req, res) 
{
  const nome_actor = `%${req.query.actor}%`;
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
      SELECT * FROM movie m
      JOIN cast c ON (m.movieID = c.movieID)
      JOIN actor a ON (c.actorID = a.actorID)
      WHERE a.actorName LIKE :nome_actor
      LIMIT :pageSize
      OFFSET :offset
    `;

  const movies = await sequelize.query(query, {
    replacements: { nome_actor, pageSize, offset },
    type: sequelize.QueryTypes.SELECT
  });

  if (movies.length === 0 && page > 1)
    return res.redirect(`/filme/actors?actor=${nome_actor}&page=1&pageSize=${pageSize}`);


  res.json(movies);

}

async function directorMovies(req, res) 
{

  const nome_director = `%${req.query.director}%`;
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
    SELECT *
    FROM movie m
    JOIN director d ON (m.directorId = d.directorId)
    WHERE d.directorName LIKE :nome_director
    LIMIT :pageSize
    OFFSET :offset
  `;

  const movies = await sequelize.query(query, {
    replacements: { nome_director, pageSize, offset },
    type: sequelize.QueryTypes.SELECT
  });

  if (movies.length === 0 && page > 1)
    return res.redirect(`/movies/director?director=${nome_director}&page=1&pageSize=${pageSize}`);

  res.json(movies);
}

async function genreMovies(req, res) 
{

  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;
  const selectedGenres = req.query.genre;
  const placeholders = selectedGenres.map(() => '?').join(',');
  const query = `
    SELECT  m.*, GROUP_CONCAT(a.actorName) AS actorNames, d.directorName
    FROM movie m 
    JOIN director d ON (m.directorId = d.directorId)
    JOIN cast c ON (m.movieId = c.movieId)
    JOIN actor a ON (c.actorID = a.actorID)
    WHERE m.genre IN (${placeholders})
    GROUP BY m.movieId
    LIMIT ${pageSize}
    OFFSET ${offset};
  `;

  const movies = await sequelize.query(query, { replacements: selectedGenres, type: sequelize.QueryTypes.SELECT });

  res.json(movies);

}

async function numberGenderEachMovies(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
        SELECT
        SUM(a.actorSex = 'Female') AS total_mulheres,
        SUM(a.actorSex = 'Male') AS total_homens
        FROM cast c
        JOIN actor a ON c.actorId = a.actorId
        LIMIT ${pageSize}
        OFFSET ${offset};
   `;

  const movies = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });

  res.json(movies);

}




module.exports = {
  listarFilmes,
  moviesOrderIMDBR,
  moviesOrderGross,
  moviesOrderRuntime,
  moviesOrderYear,
  moviesOrderName,
  nameMovies,
  releasedYearMovies,
  atorMovies,
  directorMovies,
  genreMovies,
  numberGenderEachMovies,
  filterIdMovie,
  FilmesGeneroDoAtor,
  ratingMovies


};