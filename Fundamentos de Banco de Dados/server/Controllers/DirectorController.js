const Director = require('../Models/director.js');
const { Op } = require('sequelize');
const sequelize = require('../Models/db').sequelize;


function getPaginationParams(req) 
{
  const page = Number(req.query.page) || 1;
  let pageSize
  if (req.query.pageSize < 25) 
     pageSize = Number(req.query.pageSize) || 10;
  else 
     pageSize = 25;

  return {
    page,
    pageSize,
  };
}

async function paginate(model, page, pageSize, whereClause = {}) 
{
  const totalCount = await model.count({ where: whereClause });
  const totalPages = Math.ceil(totalCount / pageSize);

  if (page > totalPages) 
    page = totalPages;
  

  const offset = (page - 1) * pageSize;
  const results = await model.findAll({
    where: whereClause,
    limit: pageSize,
    offset: offset,
  });

  return {
    results,
    totalPages,
    totalCount,
    currentPage: page,
  };
}

async function listarDiretores(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
        SELECT d.directorName, d.directorSex, COUNT(m.directorId) AS qnt_filme
        FROM movie m
        JOIN director d ON (m.directorId = d.directorId)
        GROUP BY d.directorId
        LIMIT ${pageSize}
        OFFSET ${offset}
        `;

  const directors = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });

  res.json(directors);
}


async function directorsOrderName(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
        SELECT d.directorName, d.directorSex, COUNT(m.directorId) AS qnt_filme
        FROM movie m
        JOIN director d ON (m.directorId = d.directorId)
        GROUP BY d.directorId
        ORDER BY d.directorName ${req.query.order}
        LIMIT ${pageSize}
        OFFSET ${offset}
        `;

  const directors = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });

  res.json(directors);
}

async function orderDirectorMovies(req, res) 
{

  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
        SELECT d.directorName, d.directorSex, COUNT(m.directorId) AS qnt_filme
        FROM movie m
        JOIN director d ON (m.directorId = d.directorId)
        GROUP BY d.directorId
        ORDER BY qnt_filme ${req.query.order}
        LIMIT ${pageSize}
        OFFSET ${offset}
        `;

  const directors = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });

  res.json(directors);
}

async function nameDirector(req, res) 
{
  const nome_director = `%${req.query.name}%`;
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
        SELECT d.directorName, d.directorSex, COUNT(m.directorId) AS qnt_filme
        FROM movie m
        JOIN director d ON (m.directorId =d.directorId)
        WHERE d.directorName LIKE '${nome_director}'
        GROUP BY d.directorId 
        LIMIT ${pageSize}
        OFFSET ${offset}
    `;
 

  const directors = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });


  if (directors.length === 0 && page > 1)
    return res.redirect(`/directors/filter/name?name=${nome_director}&page=1&pageSize=${pageSize}`);

  res.json(directors);

}

async function genderDirector(req, res) 
{

  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
        SELECT d.directorName, d.directorSex, COUNT(m.directorId) AS qnt_filme
        FROM movie m
        JOIN director d ON (m.directorId =d.directorId)
        WHERE d.directorSex = '${req.query.gender}'
        GROUP BY d.directorId 
        LIMIT ${pageSize}
        OFFSET ${offset}
    `;
 

  const directors = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });


  if (directors.length === 0 && page > 1)
    return res.redirect(`/directors/filter/gender?gender=${req.query.gender}&page=1&pageSize=${pageSize}`);

  res.json(directors);
  

}

async function moviesBiggersImdbrDirectors(req, res) 
{

  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
             SELECT d.directorId, d.directorName AS directorName, m.name AS movieName, m.IMDBRating
             FROM director d
             JOIN movie m ON d.directorId = m.directorId
             WHERE (
                    SELECT COUNT(*)
                    FROM movie m2
                    WHERE m2.IMDBRating > m.IMDBRating
                        AND m2.directorId = m.directorId
              ) < 5
              ORDER BY d.name, m.IMDBRating DESC
              LIMIT ${pageSize}
              OFFSET ${offset}
      `;
  const directors = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });


  res.json(directors);


}



module.exports = {
  listarDiretores,
  genderDirector,
  orderDirectorMovies,
  directorsOrderName,
  moviesBiggersImdbrDirectors,
  nameDirector


};